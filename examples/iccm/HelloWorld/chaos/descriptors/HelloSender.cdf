servants: 
  servant TaoHelloSender TAO_HelloWorld_Components_svnt:create_HelloSender_Servant

ports:
  port emits greeting_ospl => TaoHelloSender.greeting
  port emits greeting_ndds => TaoHelloSender.greeting
  port emits greeting_tcpip => TaoHelloSender.greeting