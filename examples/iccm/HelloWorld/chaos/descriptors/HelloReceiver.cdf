servants:
  servant TaoHelloReceiver TAO_HelloWorld_Components_svnt:create_HelloReceiver_Servant

ports:
  port consumes greeting_ospl => TaoHelloReceiver.greeting
  port consumes greeting_ndds => TaoHelloReceiver.greeting
  port consumes greeting_tcpip => TaoHelloReceiver.greeting
