function updateClock() {
    var now = new Date(),
        months = ['January', 'February', '...'];
        time = now.getHours() + ':' + ("0" + now.getMinutes()).slice(-2) + ':' + ("0" + now.getSeconds()).slice(-2),

        date = [now.getMonth()+1, 
				now.getDate(),
                now.getFullYear()].join('-');

    document.getElementById('time').innerHTML = [date, time].join(' // ');

    setTimeout(updateClock, 1000);
}
updateClock();