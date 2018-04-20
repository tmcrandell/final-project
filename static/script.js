
function getData(){
    $.get('/data.json',function(data){
	//convert the string data into a dictionary
	weather = JSON.parse(data);
	
	//update the DOM with the new values
	$("#indoor_temp").text(weather.indoor_temp)
	$("#indoor_humidity").text(weather.indoor_humidity)
	$("#outdoor_temp").text(weather.outdoor_temp)
	$("#outdoor_humidity").text(weather.outdoor_humidity)

	// update gauges
	$("#indoor_temp_gauge").attr("data-value",weather.indoor_temp)
	$("#outdoor_temp_gauge").attr("data-value",weather.outdoor_temp)
	$("#indoor_h_gauge").attr("data-value",weather.indoor_humidity)
	$("#outdoor_h_gauge").attr("data-value",weather.outdoor_humidity)
    });
}
    
$(function(){
    setInterval(getData,1000);
})








   
