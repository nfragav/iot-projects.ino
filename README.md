# An IOT project using Arduino and communication protocols

- HTTP
- MQTT

# Arduino + HTTP protocol

The objective of this project is using http as communication protocol, to publish data retrieved by and Arduino via sensors of our choice. To achieve this, it's vital to obtain a module which permits arduino an internet connection, and, of course, a sensor to retrieve data and be able to publish it. Here, you will find different projects (in progress) to show their specific setup and possible use cases.

For each project in this repository, you can find its general information such as used components, where to find them and possible use cases, in this README file. For project specifics such as cable and packages setup, references and a short story about the mounting of the project, go visit the project's folder and check its README file.

## Publishing Humidity and Temperature Data: DHT22, ESP-01S and Thingspeak.com
To see the project and its specifics, go to [its folder and read its documentation](/arduino-temp-http/).

### Recipe ingredients:
- [**ESP-01S**](https://es.aliexpress.com/item/32809618395.html?spm=a2g0o.order_detail.order_detail_item.3.194439d3OtaoXo&gatewayAdapt=glo2esp): A very lowcost and versatile wifi module which will let you connect to a wifi network and send an http request. There are many wifi module models, many of them utilizing the ESP8266 controller, which is the case of this controller.
- [**DHT22**](https://es.aliexpress.com/item/4001253056515.html?spm=a2g0o.order_detail.order_detail_item.2.509839d3TQBtVj&gatewayAdapt=glo2esp): A lowcost humidity and temperature sensor. Though there are some pages that refer to its inconsistency throughout different measurements, and hence its lack of precision, it is a good way to start with a project like this one. For better precision, you could get an AM2302, which you can find in the same link as the DHT22.
- **Arduino UNO**: An UNO board is more than enough to setup this project. There are many other boards which can be used, cheaper and as effective. For this project, due to the specific script and setup used, we'll stick to the UNO board.
- [**LCD I2C-controlled**](https://es.aliexpress.com/item/1005006955896871.html?spm=a2g0o.productlist.main.5.203eOIULOIULVd&algo_pvid=a24861c3-7a90-4599-8744-485ccfb8a785&algo_exp_id=a24861c3-7a90-4599-8744-485ccfb8a785-2&pdp_npi=4%40dis%21CLP%212911%212637%21%21%213.08%212.79%21%402103277f17173593868883531e1f72%2112000038848810097%21sea%21CL%212196304125%21&curPageLogUid=qLn5KA0mkct8&utparam-url=scene%3Asearch%7Cquery_from%3A): A simple LCD with an easy configuration and package installation such as this will let you see the data in a more instant manner. This will serve the purpose of getting to know immediatly the temperature of humidity detected by the sensor. This will make unnecessary to log into [Thingspeak](https://thingspeak.com/) each time we want to know the current temperature and humidity.

#### Description
The project consists in an UNO board which controls a sensor, wifi module and LCD in order to display and register room's temperate and humidity. The historical temperature and humidity measurements that the sensor catches are pushed to [Thingspeak](https://thingspeak.com/), which provides a simple database to store data fields. 

#### Use Cases
This kind of project uses the HTTP communication protocol, and because of that, it may be helpful to apply it in the following cases:
- You got an API you can reach through HTTP to store the received data.
- A central server which will process the data.
- Simply visualizing data by entering [thingspeak](https://thingspeak.com/) registers.
This project does not use MQTT, for which I would not recommend trying to make any other device make an action based on the publication, unless you are willing to retrieve an API's status data with your devices and make their effectors do an action. This approach is a secure but inefficient one.
