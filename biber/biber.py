import serial
import sys
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.websocket

from tornado.options import define, options
define("device", default="/dev/ttyUSB0", help="serial device name, like /dev/ttyUSB0", type=string)
define("baudrate", default=115200, help="serial device baud rate, like 115200", type=int)
define("port", default=8080, help="run on the given port", type=int)

ser = serial.Serial(options.device)
duration = 100

class IndexHandler(tornado.web.RequestHandler):
    def get(self):
        self.render('index.html')

class WebSocketHandler(tornado.websocket.WebSocketHandler):
    def open(self):
        print 'new connection'
        self.write_message("connected")

    def on_message(self, message):
        print 'message received %s' % message
        self.write_message('message received %s' % message)

    def on_close(self):
       print 'connection closed'

def main(argv):
    print "Opening serial device at " + options.device
    ser = serial.Serial(device, options.baudrate)
    
    app = tornado.web.Application(
        handlers=[
            (r"/", IndexHandler),
            (r"/ws", WebSocketHandler)
        ]
    )
    httpServer = tornado.httpserver.HTTPServer(app)
    httpServer.listen(options.port)
    print "Listening on port:", options.port
    tornado.ioloop.IOLoop.instance().start()
    

def left(duration):
    ser.write(b'0,'+duration)

def right(duration):
    ser.write(b'1'+duration)

def forward(duration):
    ser.write(b'2'+duration)

def backward(duration):
    ser.write(b'3'+duration)

def setSpeed(speed):
    ser.write(b'4'+speed)

##############################################################
if __name__ == "__main__":
    tornado.options.parse_command_line()
    main(sys.argv)
