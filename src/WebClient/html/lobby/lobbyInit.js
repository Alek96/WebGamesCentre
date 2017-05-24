
console.log("Initialize roominit");

loadFile("lobby/lobbyLoad.js", callFunction, ['addState', 'LobbyLoad', 'lobbyLoad']);
loadFile("lobby/lobby.js", callFunction, ['addState', 'Lobby', 'lobby']);

loadFile("lobby/lobbyBoot.js", callFunction, ['addState', 'LobbyBoot', 'lobbyBoot', true]); //must be the last one