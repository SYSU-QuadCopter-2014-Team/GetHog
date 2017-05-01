# GetHog
基于OpenCV 2.4批量提取图像Hog特征并输出为SVM训练集。

运行前准备：
准备好正负样本集，正样本集文件路径列表为positive.txt，负样本集文件路径列表为negative.txt。均放在根目录下。

运行将生成hog.txt，可作为SVM训练器的输入。

编译与运行：

```
cmake .
make
./GetHog
