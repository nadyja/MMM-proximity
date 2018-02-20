//MMM-proximity.js:


Module.register("MMM-proximity", {
	defaults: {
	},
  start: function(){
		this.displayText = 'start';
		this.smallText = '';
	},

	getDom: function() {
		var wrapper = document.createElement("div");

  	var h1 = document.createElement("h1");
		var h2 = document.createElement("small");
		h1.innerHTML = this.displayText;
		h2.innerHTML = this.smallText;
		wrapper.appendChild(h1);
		wrapper.appendChild(h2);
		return wrapper;
	},
	socketNotificationReceived: function(notification, payload, sender) {

		switch(notification) {
			case 'PROXIMITY_EMPTY':
				this.displayText='Come closer';
				this.smallText='';
				this.updateDom(500);
				break;
			case 'PROXIMITY_PASSING':
				this.displayText='I see you';
				this.smallText='...';
				this.updateDom(500);
				break;
			case 'PROXIMITY_THERE':
				this.displayText='I see you';
				this.smallText='to talk to me say "Alexa"';
				this.updateDom(0);
				break;
			default:
		}


	},
	notificationReceived: function(notification, payload, sender) {
		if(notification === 'DOM_OBJECTS_CREATED'){
				this.sendSocketNotification('SET_CONFIG', this.config);
		}
	}
});
