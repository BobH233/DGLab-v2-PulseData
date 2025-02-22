# DGLab-v2 波形原始ble数据

该项目通过模拟郊狼二代电击器的蓝牙协议，捕获DGLab App内置的波形数据，以期望获得原始的App的波形预设体验

该项目使用乐鑫ESP32-Devkit进行蓝牙协议模拟，模拟所用的所有代码可参见`ESP32-DGLabSimu`文件夹


![esp32-devkit](./doc/esp32.jpg)

利用ESP32捕获的全部原始数据在`OriginalData`文件夹中