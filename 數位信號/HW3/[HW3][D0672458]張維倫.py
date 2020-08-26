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
plt.plot(time,wave_data,linewidth=0.5)
high = list(wave_data)
for i in range(1,nframes):
    high[i] = high[i] - high[i-1]
high = np.short(high)
plt.plot(time,high,linewidth=0.5,color = 'orange')
plt.title('After highpass')


plt.figure(3)
plt.plot(time,wave_data,linewidth=0.5)
low = list(wave_data)
for i in range(1,nframes):
    low[i] = 1/3*(1/3*low[i]+1/3*low[i-1]+1/3*low[i-2])
low = np.short(low)
plt.plot(time,low,linewidth=0.5,color = 'orange')
plt.title('After lowpass')

#打開WAV文檔
f  =  wave . open (r"105977_highpass.wav" ,  "wb" )
#配置聲道數、量化位數和取樣頻率
f . setnchannels ( 1 )
f . setsampwidth ( 2 )
f . setframerate ( framerate )
#將wav_data轉換為二進制數據寫入文件
f . writeframes ( high . tostring ())
f . close ()

#打開WAV文檔
f  =  wave . open (r"105977_lowpass.wav" ,  "wb" )
#配置聲道數、量化位數和取樣頻率
f . setnchannels ( 1 )
f . setsampwidth ( 2 )
f . setframerate ( framerate )
#將wav_data轉換為二進制數據寫入文件
f . writeframes ( low . tostring ())
f . close ()
plt.show()