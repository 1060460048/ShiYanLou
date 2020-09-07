# TVM_深度学习编译器

[tvm.d2l.ai 笔记](https://github.com/Ewenwan/learning_tvm)

[tvm.schedule 自动 代码 生成 调度 ](https://github.com/StrongSpoon/tvm.schedule)

[tvm在线文档](https://tvm.apache.org/docs/install/index.html)

[在TVM中添加新设备Codegen](https://zhuanlan.zhihu.com/p/108071133)

[tvm会议](//sampl.cs.washington.edu/tvmconf/)

[课程资料](https://github.com/Ewenwan/d2l-tvm)

[在android上安装和运行tvm ](https://www.dazhuanlan.com/2020/03/07/5e6379972ef57/)

## TVM 使用示例
```python
# 矩阵赋值

import tvm

A = tvm.placeholder((10, 10))
B = tvm.compute((10, 10), lambda i, j: A[i, j])
s = tvm.create_schedule(B.op)     # 调度
f = tvm.build(s, [A, B], "hello") # 编译生成代码
print(f.get_source())             # 打印生成的代码
```
> 生成的代码
```c
// hello tvm backend!
void default_function( void* args,  void* arg_type_ids, int32_t num_args,  void* out_ret_value,  void* out_ret_tcode) {
  // ......
  float* placeholder = (float*)(((DLTensor*)arg0)[0].data);
  // ......
  float* compute = (float*)(((DLTensor*)arg1)[0].data);
  // ......
  for (int32_t i = 0; i < 10; ++i) {
    for (int32_t j = 0; j < 10; ++j) {
      compute[((i * 10) + j)] = placeholder[((i * 10) + j)]; // 矩阵赋值
    }
  }
}

```

# tvm 调用分析

[TVM代码走读（九） 计算和调度](https://zhuanlan.zhihu.com/p/166551011)

```py
import tvm
from tvm import te
import numpy as np

A = te.placeholder((m, n), name='A')
B = te.placeholder((m, n), name='B')
C = te.compute((m, n), lambda i, j: A[i, j] * B[i, j], name='C')
```

compute python 接口  python/tvm/te/operation.py  def compute(shape, fcompute, name="compute", tag="", attrs=None): 函数
```py
def compute(shape, fcompute, name="compute", tag="", attrs=None):
 """Construct a new tensor by computing over the shape domain.
    The compute rule is result[axis] = fcompute(axis)
    Parameters
    ----------
    shape: Tuple of Expr
        The shape of the tensor
    fcompute: lambda function of indices-> value
        Specifies the input source expression
        计算函数
    name: str, optional
        The name hint of the tensor
    tag: str, optional
        Additional tag information about the compute.

    attrs: dict, optional
        The additional auxiliary attributes about the compute.
    Returns
    -------
    tensor: Tensor
        The created tensor


    if isinstance(body, _tensor.TensorIntrinCall):
        for i, s in enumerate(shape[out_ndim:]):
            var_name = "ax" + str(i)
            dim_var.append(tvm.tir.IterVar((0, s), var_name, 4))
        op_node = _ffi_api.TensorComputeOp(name,
                                           tag,
                                           dim_var,
                                           body.reduce_axis,
                                           out_ndim,
                                           body.intrin,
                                           body.tensors,
                                           body.regions,
                                           body.scalar_inputs)
    else:
        if not isinstance(body, (list, tuple)):
            body = [body]
        body = convert(body)
        op_node = _ffi_api.ComputeOp(
            name, tag, attrs, dim_var, body)
```

调用链 python/tvm/te/operation.py [def compute() 函数 ] ---> _ffi_api.TensorComputeOp()  ---> src/te/operation/compute_op.cc   ComputeOp::ComputeOp()

```c
ComputeOp::ComputeOp(std::string name, std::string tag, Map<String, ObjectRef> attrs,
                     Array<IterVar> axis, Array<PrimExpr> body) {
  if (!attrs.defined()) {
    attrs = Map<String, ObjectRef>();
  }
  auto n = make_object<ComputeOpNode>();
  n->name = std::move(name);
  n->tag = std::move(tag);
  n->attrs = std::move(attrs);
  n->axis = std::move(axis);
  n->body = std::move(body);
  if (n->body[0]->IsInstance<tir::ReduceNode>()) {
    const tir::ReduceNode* reduce = n->body[0].as<tir::ReduceNode>();
    n->reduce_axis = reduce->axis;
  }
  VerifyComputeOp(n.get());
  data_ = std::move(n);
}



```

te.compute可以总结为如下几步:

    根据传入的fcompute,翻译成对应的表达式传入.
    生成ComputeOpNode,记录计算节点.
    根据计算节点,返回计算节点输出对应的Tensor.




## TVM 中 Relay 涉及到的 Pass 优化操作

> Concept

一种 Pass 代表一种优化。比较多在 LLVM 中提到。

ModulePass是将整个程序视作一个单元处理的pass。

FunctionPass是以单个函数为作用域的pass, 每个函数间是相互独立的。

> Pass 

high-level pass：

header file: include/tvm/relay/transforms.h 
src files: src/relay/pass 
python: python/tvm/relay/transform.py

tensort level IR pass:  

header file include/tvm/tir/ir_pass.h 
src files: src/tir/pass python: python/tvm/tir/ir_pass.py

本文只涉及到 high-level pass。

tensort level IR pass 更多的是底层代码生成时做的优化，如 VectorizeLoop，UnrollLoop，InjectPrefetch，StorageRewrite 等。


> ModulePass

1. LambdaLift 将局部函数提升为全局函数。 

在 src/relay/backend/vm/compiler.cc, src/relay/backend/vm/lambda_lift.cc。 

2. RemoveUnusedFunctions 去掉 relay 的 IR 模块中未使用的函数。  

Inline 将一个被 inline 标记的全局函数嵌入到 relay 的IR模块中。 

3. EtaExpand 为构造函数添加抽象，或者给一个函数添加全局变量。
如： square 被转化为 fn (%x:  int32) -> int32 { square(x) }  See https://en.wikipedia.org/wiki/Lambda_calculus#%CE%B7-conversion  

4. PartialEval 在编译时评估静态的代码碎片，尽可能多的做常量传播，常量折叠，代码嵌入等优化，以减少运行时开销，获得更多的融合优化。作为代价生成的code量会增加。 

5. PrintIR 打印IR。通常作为一系列 pass 的结果，用来debug。 

6. PartitionGraph 将一个混合后端的relay程序分割到各自后端的计算区域。  

7.  ToANormalForm 将一个数据流图转化为行政范式 (Administrative Normal Form, A-Normal Form, ANF)。 将一个表达从隐式共享的图的形式转化为显式共享， 也就是 ANF。 The scope of the root expression is the global scope. The scope of any non root expression is the least common ancestor of all it's scope. Values are ordered by post-DFS order in each scope.


> FunctionPass

1. DeadCodeElimination 去掉不影响程序结果的表达。将没有被索引到的 let bindings 去掉，将被使用过一次的 let bindings 作为代码嵌入。 

2. FoldConstant 折叠常量函数。 

3. FuseOps 融合算子，可以指定融合的优化级别  

4. RewriteAnnotatedOps 重写被注释的算子， 比如 on_device 会标记在哪一种设备上进行调度计算。帮助进行异构计算执行。  

5. ToCPS 将一个表达转化为连续传递式样 (continuation passing style, CPS)。 CPS 意思是每一个函数将不会直接返回结果，而是传递一个另外的函数，作为参数，然后将结果传到下一个续集。这样每一个函数调用时将会多一个参数，表示其余的计算。每一个中间计算都会被传入一个续集。  

6. ToGraphNormalForm 去除所有的 let binding, 并将所有的变量转化为直接的指针索引。返回的表达叫做 graph normal form。  

7. SimplifyInference 在推理时简化一些特定的算子，比如 batchnorm 会被代替为一些更加简单的算子。这部分 Efficient Deep Learning Inference on Edge Devices 有写。  

8. FastMath 将非线性激活函数替换成近似计算的算子以获得更快的计算速度。一些情景下有损失计算精度的风险。  InferType 推理一个表达式的类别。获得的结果是一个有显式类别信息的新表达式，以及它的返回类型。

9. EliminateCommonSubexpr 寻找并去掉共同的子表达式。比如有两个表达式被评估为等同，则新建一个变量来替代它们两个。  

10. CombineParallelConv2D     将并行运算的二维卷积合成为一个卷积，如果合成的卷积的分支数大于某个最小值。  

11. CombineParallelDense     将并行运算的稠密算子合并为批处理的矩阵乘法 (batch_matmul)，如果合成的算子的分支数小于某个最小值。  

12. BackwardFoldScaleAxis / ForwardFoldScaleAxis     将轴的缩放折叠进卷积或者稠密算子的weights中 https://github.com/apache/incubator-tvm/pull/2020  

13. CanonicalizeOps 将一些深度学习的算子规范化为一系列简化的算子，比如将 bias_add 规范化为先进行 expand_dims 然后做 broadcast_add 

14. AlterOpLayout 转换算子的布局，或者将元算子替换为其他表达式。可以用来计算定制数据布局的卷积，或者更加通用的weights的前置转换。 

15. ConvertLayout 给定一个目标的数据布局，将表达式大多数算子的数据布局转化为目的布局。在理想情况下，只有两个起始和结束的布局需要转换。一般在relay转化别的框架时需要。主要使用 AlterOpLayout 和 InferCorrectLayout。 

16. RFC - https://discuss.tvm.ai/t/layout-conversion-pass/4009  

17. Legalize 将一个表达式转化为另一个表达式 (expr)，可以基于算子的shape，dtype，或者 data layout 转化为另一个算子或者一系列算子。一般在target平台相关的优化中，两个语等价的算子性能不一定会一样。  

18. CanonicalizeCast 规范化 cast 表达式，使得算子的融合更加方便。 

19. MergeComposite 将多个模式相匹配的算子合并为一个复合算子。主要用在使用外部代码生成工具时多个算子map到同一个外部算子的情况。定义作为Wrapper使用。 在 src/relay/pass/annotate_target.cc 

12. AnnotateTarget 将表达式中的算子标注编译器或者部署平台，使得算子被wrap为 compiler_begin／subgraph_start 和 compiler_end ／subgraph_end，从而用做之后其他编译器的代码生成。定义作为Wrapper使用。 在 src/relay/pass/annotate_target.cc



