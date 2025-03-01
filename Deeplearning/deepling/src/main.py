import torch
# 1. 创建一个5行3列的随机张量X
X = torch.rand(5, 3)

# 2. 使用PyTorch内置函数检测X的shape，dtype，device
print("X的shape:", X.shape)
print("X的dtype:", X.dtype)
print("X的device:", X.device)
print("-----------")

# 3. 直接创建一个[[1,2,3,4,5],[6,7,8,9,10],[11,12,13,14,15]]的张量Y
Y = torch.tensor([[1, 2, 3, 4, 5],
                  [6, 7, 8, 9, 10],
                  [11, 12, 13, 14, 15]])


# 4. 将Y的维度转换为5行3列
Y = Y.view(5, 3)
print(" Y:", Y)
print("-----------")

# 5. 实现X和Y的加减乘除
# 确保Y和X的形状相同，以便进行逐元素运算
Z_add = X + Y
Z_sub = X - Y
Z_mul = X * Y
Z_div = X / Y

print("X + Y:", Z_add)
print("X - Y:", Z_sub)
print("X * Y:", Z_mul)
print("X / Y:", Z_div)
print("-----------")
# 6. 了解abs()，sqrt()，neg()，mean()的作用
print("abs()的作用:", Y.abs())                              #abs(): 绝对值
print("sqrt()的作用:", Y.float().sqrt())                    # 需要将Y转换为浮点数来进行开方运算
print("neg()的作用:", Y.neg())                              #neg(): 取反
print("mean()的作用:", X.mean())                            #mean(): 求平均值
print("-----------")

# 7. 内置函数max()，argmax()，sum()，以及其dim参数的作用
print("max()参数的作用:", Y.max())
print("argmax()参数的作用:", Y.argmax())
print("sum()参数的作用:", Y.sum())
print("-----------")

# 使用dim参数来在不同维度上操作
print("dim参数来在0:", Y.max(dim=0))                        #在第 0 维（行方向）上执行，对每一列计算结果
print("dim参数来在1:", Y.sum(dim=1))                        #在第 1 维（列方向）上执行，对每一行计算结果
print("-----------")

# 8. 将张量X转为Numpy格式，再转回来
X_numpy = X.numpy()
X_back_to_tensor = torch.from_numpy(X_numpy)
print("将张量X转为Numpy格式，再转回来:", X_back_to_tensor)
print("-----------")

# 9. 将张量X放到CUDA上
if torch.cuda.is_available():
    X_cuda = X.to("cuda")
    print("将张量X放到CUDA上:", X_cuda)
else:
    print("CUDA is not available.") 
print("-----------")

#输出x,y
print(X)
print(Y)
print("-----------")

# 10. 张量的拼接，解压，压缩，广播
# 拼接
concat_XY = torch.cat((X, Y), dim=0)  # 在行上拼接
print("拼接:", concat_XY)
print("-----------")

# 解压（沿维度分离）
split_X = torch.chunk(X, chunks=5, dim=0)  # 将X分成5个张量
print("解压（沿维度分离）:", split_X)
print("-----------")

# 压缩（将零元素去除）
compressed_Y = Y[Y > 0]  # 仅保留非零元素
print("压缩（将零元素去除）:", compressed_Y)
print("-----------")

# 广播（自动扩展维度匹配运算）
X_broadcast = X + Y[0]  # Y[0] 维度为(3,), 通过广播可以与 X 进行相加
print("广播（自动扩展维度匹配运算）:", X_broadcast)
print("-----------")

# 使用Numpy的transpose函数
Y_np = Y.numpy()
Y_transposed = torch.from_numpy(Y_np.transpose())
print("使用Numpy的transpose函数:", Y_transposed)
print("-----------")
