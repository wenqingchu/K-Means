在test.cpp中通过系统调用，以命令行参数的形式调用K-Means.exe
通过递归来实现2^16中初始partion方案的测试

调用方式为 K-Means.exe filename matrixname clusters threshold partion

其中partion 的格式为 1 1 1 1 1 1 1 1 1 1 2 1 2 1 2 1
依次指定16个向量处于哪一个类


filename是.mat文件，其中保存了矩阵数据
matrixname是要读取的矩阵的名字
clusters是聚类的个数
threshold是针对Lloyd方法时的边界条件

=======
