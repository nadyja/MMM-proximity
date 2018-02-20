var NodeHelper = require('node_helper');
// const request = require('request');
// var SerialPort = require("serialport");

module.exports = NodeHelper.create({
    start: function() {

    },
    socketNotificationReceived: function(notification, payload) {
      if(notification === 'SET_CONFIG'){

        var self = this;
        var serialport = new SerialPort("/dev/ttyACM0");
        // serialport.on('open', function(){
      //     serialport.on('data', function(data){
      //         var proximityStateChange = data[0];
      //
      //         switch(proximityStateChange) {
      //           case 0:
      //             self.sendSocketNotification('PROXIMITY_EMPTY', {});
      //             break;
      //           case 1:
      //             self.sendSocketNotification('PROXIMITY_PASSING', {});
      //             break;
      //           case 2:
      //             self.sendSocketNotification('PROXIMITY_THERE', {});
      //             break;
      //           default:
      //         }
      //     });
        // });
      }
    }
});
