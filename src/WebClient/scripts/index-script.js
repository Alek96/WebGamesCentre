var header = document.querySelector('h1');

header.textContent += '. Welcome!';

// FIXME add port number to which the server is bound!
// FIXME change localhost to server's machine IP addr!
// inside the WebSocketRequestHandler
var socket = new WebSocket("ws://localhost/logon"); // ws://addr:port/path
console.log("socket created");

socket.onopen = function (event) {
    console.log("onopen entered");
    //socket.send("Test WebSocket connection (onopen).");
};

// socket.send("Test WebSocket connection (immediate).");

var answerPar = document.getElementById("ws-answer");
var button = document.getElementById("send-btn");
var textArea = document.getElementById("txt-area");
var errMsg = document.getElementById("err-msg");
console.log("answerPar: " + answerPar);
console.log("button: " + button);
console.log("textArea: " + textArea);
console.log("errMsg: " + errMsg); 

socket.onmessage = function (event) {
    console.log("onmessage entered");
    console.log("Received: " + event.data);

    answerPar.textContent += event.data;

    //socket.close();
    //console.log("socket closed");
};

button.onclick = function (/*event*/) {

    if (textArea.value.length === 0) {   // is textArea is empty
        errMsg.innerText = "You cannot send an empty message!";
        return;
    }
    errMsg.innerText = "";

    // TODO check if socket is open
    var chatMessage = {
        player: {
            name: "Player1",
            id: 1
        },
        msg: {
            text: null,
            time: Date.now()
        }
    };

    chatMessage.msg.text = textArea.value;
    var message = JSON.stringify(chatMessage);
    //textArea.value = " " + textArea.value + " ";
    //chatMessage.message.text = textArea.value;

    socket.send(message);    // send 0 bytes => close connection (on the server) !!!
    console.log("JSON-formatted message sent. Length: " + message.length);

    textArea.value = "";
};

socket.onerror = function (what) {
    console.log("Got error from WS. Error:");
    console.log(what);
}

document.getElementById("ws-close").onclick = function () {
    // TODO check if socket is open

    // Status codes, see: https://tools.ietf.org/html/rfc6455#section-7.4.1
    // normal closure
    socket.close(1000);
    console.log("WebSocket closed");
};



// socket.close();
// console.log("socket closed");