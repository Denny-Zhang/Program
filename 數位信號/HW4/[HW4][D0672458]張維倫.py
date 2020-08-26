# 參考資料:https://blog.csdn.net/ouening/article/details/71079535

import wave
import numpy as np
import pylab as plt
from scipy import  *

#打开wav文件 ，open返回一个的是一个Wave_read类的实例，通过调用它的方法读取WAV文件的格式和数据。
f = wave.open(r"105977__wcfl10__favorite-station.wav","rb")
#读取格式信息
#一次性返回所有的WAV文件的格式信息，它返回的是一个组元(tuple)：声道数, 量化位数（byte单位）, 采
#样频率, 采样点数, 压缩类型, 压缩类型的描述。wave模块只支持非压缩的数据，因此可以忽略最后两个信息
params = f.getparams()
nchannels, sampwidth, framerate, nframes = params[:4]
#读取波形数据
#读取声音数据，传递一个参数指定需要读取的长度（以取样点为单位）
str_data  = f.readframes(nframes)
f.close()

#将波形数据转换成数组
#需要根据声道数和量化单位，将读取的二进制数据转换为一个可以计算的数组
wave_data = np.frombuffer(str_data,dtype = np.short)

#通过取样点数和取样频率计算出每个取样的时间。
time=np.arange(0,nframes)
print(params)

plt.figure(1)
# time 也是一个数组，与wave_data[0]或wave_data[1]配对形成系列点坐标
plt.plot(time,wave_data,linewidth=0.5)

plt.figure(2)
yf1=abs(fft(wave_data))/len(time)           #归一化处理
xf = np.arange(len(wave_data))        # 频率
xf1 = xf
plt.plot(xf1,yf1,linewidth=0.5,color = 'orange')
plt.title('frequency domain')


plt.figure(3)
yf1 = abs(fft(wave_data)) / 1024 # 归一化处理
xf = np.arange(len(wave_data))        # 频率
xf1 = xf
plt.plot(xf1,yf1,linewidth=0.5,color = 'orange')
plt.title('1024 dot frequency domain')


plt.show()