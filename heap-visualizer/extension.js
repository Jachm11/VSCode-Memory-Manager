// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');
const net = require('net');

// this method is called when your extension is activated
// your extension is activated the very first time the command is executed

//legend: {
	//onClick: info
//},

/**
 * @param {vscode.ExtensionContext} context
 */
function activate(context) {

	// Use the console to output diagnostic information (console.log) and errors (console.error)
	// This line of code will only be executed once when your extension is activated
	console.log('Congratulations, your extension "heap-visualizer" is now active!');

	// The command has been defined in the package.json file
	// Now provide the implementation of the command with  registerCommand
	// The commandId parameter must match the command field in package.json
	let disposable = vscode.commands.registerCommand('heap-visualizer.helloWorld', function () {
		// The code you place here will be executed every time your command is executed
		// Display a message box to the user
		vscode.window.showInformationMessage('Hello World from heap visualizer!');
	});

	
	let init = vscode.commands.registerCommand('heap-visualizer.start',function(){

		// Message for user
		vscode.window.showInformationMessage('Heap Visualizer initialized!');


		// Create the webview panel
		const panel = vscode.window.createWebviewPanel(
			'HS',
			'Heap Visualizer',
			vscode.ViewColumn.One,
			{
				enableScripts: true
			}
		);


		// Set the webview panel to a HTML
		panel.webview.html = getWebviewContent();



		// Handle messages from the webview
		var registered = false;  
      	panel.webview.onDidReceiveMessage(
        	message => {
          		switch (message.command) {
            	case 'connect':
					if (!registered){
						clientSrv.write("p "+message.text);
						//vscode.window.showInformationMessage(message.text);
						return;
					}else{
						vscode.window.showInformationMessage("You are already logged!");
					  	return;
					}
				case 'empty':
					vscode.window.showErrorMessage("Password field is empty!");
					return;

				case 'empty2':
					vscode.window.showErrorMessage("Id field is empty!");
					return;
					  
				case 'save':
					clientLib.write('2');
					return;

				case 'asked':
					vscode.window.showInformationMessage("Asked for VSPtr Id="+message.text);
					clientSrv.write("id "+message.text);
					return;
				}
        	},
        	undefined,
        	context.subscriptions
      	);

		// Create a complete HTML for the webView
		function getWebviewContent(labels,data,dirs) {
			return `<!DOCTYPE html>
			<html lang="en">
			<head>
			<meta charset="UTF-8">
			<meta name="viewport" content="width=device-width, initial-scale=1.0">
			<title>Heap Visualizer</title>
			<script src="https://cdn.jsdelivr.net/npm/chart.js@2.9.3/dist/Chart.min.js"></script>
			</head>
			<body>
            <canvas id="myChart" width="400" height="400"></canvas>
			<script>
				const vscode = acquireVsCodeApi();
                var ctx = document.getElementById('myChart').getContext('2d');
                var myChart = new Chart(ctx, {
                    type: 'bar',
                    data: {
                        labels: [${labels}],
                        datasets: [${data}]
                    },
                    options: {
                        scales: {
                            yAxes: [{
                                ticks: {
                                    beginAtZero: true
                                }
                            }]
                        }
					}
					
					
				});


				</script>
				<p>Direcciones de memoria por dato:<br><br>${dirs}</p>
				<p></p>
                <button style="background-color:#007bcd; border-color:#007bcd; color:white", onclick="document.getElementById('id01').style.display='block'" style="width:auto;">Connect to server</button>
	
                <div id="id01" class="modal" style="display: none">

					<div class="container">
                    <p></p>

                    <label><b>Password</b></label>
                    <input type="password" placeholder="Enter Password" id="psw">
                    <button id= "passwordLogin", style="background-color:#007bcd; border-color:#007bcd; color:white">Login</button>

                    </div>
                    <div class="container">
                    <button type="button", style="background-color:#007bcd; border-color:#007bcd; color:white" onclick="document.getElementById('id01').style.display='none'" class="cancelbtn">Cancel</button>
					</div>	
				</div>
				

				<p>Funciones de servidor:<br></p>
				<button id="save" disabled>Save pointers</button>
				<button id="ask", onclick="document.getElementById('id02').style.display='block'" disabled>Ask for VSPtr data</button>

				<div id="id02" class="modal" style="display: none">

					<div class="container">
					<br>
					<label ><b>VSPtr ID</b></label>
					<input placeholder="Enter VSPtr ID" id="id">
					<button id= "idSend", style="background-color:#007bcd; border-color:#007bcd; color:white">Send</button>

					</div>
					<div class="container">
					<button type="button", style="background-color:#007bcd; border-color:#007bcd; color:white" onclick="document.getElementById('id02').style.display='none'" class="cancelbtn">Cancel</button>
					</div>
				</div>
				

                
                <script>

  					document.getElementById("passwordLogin").addEventListener('click',function(){
						var pws = document.getElementById("psw").value;
						if (pws != ''){
							var modal = document.getElementById('id01');
							modal.style.display = "none";
							vscode.postMessage({
								command : 'connect',
								text : ""+pws+""
							})
							document.getElementById("passwordLogin").clear;
						}else{
							vscode.postMessage({
								command : 'empty'
							})
						}
					});

					document.getElementById("save").addEventListener('click',function(){
						vscode.postMessage({
							command : 'save'
						})
					});

					document.getElementById("idSend").addEventListener('click',function(){
						var ask = document.getElementById("id").value;
						if (ask != ''){
							var modal = document.getElementById('id02');
							modal.style.display = "none";
							vscode.postMessage({
								command : 'asked',
								text : ""+ask+""
							})
						}else{
							vscode.postMessage({
								command : 'empty2'
							})
						}
					});

					window.addEventListener('message', event => {

						const message = event.data; // The JSON data our extension sent
			
						switch (message.command) {
							case 'connected':
								var save = document.getElementById("save");
								save.style.background ='#007bcd';
								save.style.borderColor = '#007bcd';
								save.style.color = 'white';
								save.disabled = false;

								var ask = document.getElementById("ask");
								ask.style.background ='#007bcd';
                                ask.style.borderColor = '#007bcd';
                                ask.style.color = 'white';
								ask.disabled = false;
								
								break;
						}
					});


                </script>
			</body>
			</html>`;
		}

		
	//              _________________________________
	//_____________/Create a client for the library

		const clientLib = net.createConnection({port:54000},()=>{
			if ( !clientLib.address){
				console.log("Failed to connect")
			}else{
				clientLib.write('1');
				console.log('Connected to lib!');
			}
		});

		clientLib.on('data',(data)=>{
			parseData(data.toString());
		});
		clientLib.on('end',()=>{
			console.log('Disconneted frim library!');
			vscode.window.showErrorMessage("Disconnected from library");

			});


		const getData= ()=>{
			clientLib.write('1');
		}

		const dataRetrive = setInterval(getData,3000);
	//_________________________________________________________________________

	//              _________________________________
	//_____________/Create a client for the server

		const clientSrv = net.createConnection({port:8888},()=>{
			if ( !clientSrv.address){
				console.log("Failed to connect")
			}else{
				console.log('Connected to server!')
			}
		});

		clientSrv.on('data',(data)=>{
			parseSrvData(data.toString());
		});
		clientSrv.on('end',()=>{
			console.log('Disconneted from server!');
			vscode.window.showErrorMessage("Disconnected from server")
			});
	//_________________________________________________________________________
	


	//                ___________________________________
	//_______________/Date treatment for HTML display

		function parseData(info){

			if (info[0] == "{"){
				sendPtr(info);
				return;
			}
			var x = info.split(";");
			x = x.slice(0,(x.length)-1);
			var dir ="" ;
			var data = "";
			
			x.forEach(e => {
				var y = e.split(",");

				var dataArr = makeDataArr(y[0],y[3]);
				var dataSet;

				dataSet = "{\nlabel:'"+y[1]+"',\ndata:["+dataArr+"],\nbackgroundColor:['"+getRandomRgb(0)+"','"+getRandomRgb(1)+
				"','"+getRandomRgb(2)+"','"+getRandomRgb(3)+"','"+getRandomRgb(4)+"','"+getRandomRgb(5)+"','"+getRandomRgb(6)+"','"+
				getRandomRgb(7)+"','"+getRandomRgb(8)+"'],\nborderColor:['"+getRandomRgb(0)+"','"+getRandomRgb(1)+"','"+getRandomRgb(2)+
				"','"+getRandomRgb(3)+"','"+getRandomRgb(4)+"','"+getRandomRgb(5)+"','"+getRandomRgb(6)+"','"+getRandomRgb(7)+"','"+
				getRandomRgb(8)+"'],\nborderWidth:1\n},";
				
				dir = dir + y[1] + " : " + y[2] + " (long)"+"<br>";

				data = data + dataSet;
			});

			var labels = "'int','double','char','string','bool','float','short','unsigned','class'";

			
			panel.webview.html = getWebviewContent(labels,data.substring(0, data.length - 1),dir);

		}

		function makeDataArr(tipo,dato){
			if (tipo == "int"){
                var valor = [dato,'','','','','','','',''];
			}else if(tipo == "double"){
                var valor = ['',dato,'','','','','','',''];
			}else if(tipo == "char"){
                var valor = ['','',dato,'','','','','',''];
			}else if(tipo == "string"){
                var valor = ['','','',dato,'','','','',''];
			}else if(tipo == "bool"){
                var valor = ['','','','',dato,'','','',''];
			}else if(tipo == "float"){
                var valor = ['','','','','',dato,'','',''];
			}else if(tipo == "short"){
                var valor = ['','','','','','',dato,'',''];
			}else if(tipo == "unsigned"){
                var valor = ['','','','','','','',dato,''];
			}else{
                var valor = ['','','','','','','','',dato];
			}
			return valor;
		}

		function getRandomRgb(x) {
			if (x == 0){
				var r = 0;
				var g = 122;
				var b = 205;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else if (x==1){
				var r = 52;
				var g = 235;
				var b = 219;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			} else if (x==2){
				var r = 52;
				var g = 235;
				var b = 155;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else if(x==3){
				var r = 52;
				var g = 235;
				var b = 91;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else if(x==4){
				var r = 164;
				var g = 235;
				var b = 52;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else if(x==5){
				var r = 229;
				var g = 235;
				var b = 52;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else if(x==6){
				var r = 230;
				var g = 147;
				var b = 39;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else if(x==7){
				var r = 164;
				var g = 74;
				var b = 237;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}else{
				var r = 209;
				var g = 8;
				var b = 8;
				return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
			}
		}

	//___________________________________________________________________________


	//                _____________________________________
	//_______________/Date treatment for server interaction


	function parseSrvData(data){
		switch (data){
			case 'goodpass':
				vscode.window.showInformationMessage("Succesfully connected!");
				registered = true;
				panel.webview.postMessage({ command: 'connected' });
				return;

			case 'badpass':
				vscode.window.showErrorMessage("Incorrect password");
				return;

			case 'hasaccess':
				vscode.window.showErrorMessage("Already logged in!");
				return;

			case 'ptrssaved':
				vscode.window.showInformationMessage("VSPtr's saved in server!");
				return;

			case 'noptrs':
				vscode.window.showErrorMessage("Server is empty: Please save some VSPtr's first");
				return;

			case 'notfound':
				vscode.window.showErrorMessage("VSPtr not found");
				return;

			case 'noaccess':
				vscode.window.showInformationMessage("You dont have accesses to the server!");
				return;

			case 'notrecognized':
				vscode.window.showInformationMessage("Unknown request to server");
				return;

			default:
				showJson(data);
				return;
				
		}
		
	}

	function showJson(data){
		vscode.window.showInformationMessage("Pointer data is: "+data);
		console.log(data);
	}

	//Echoes the Lib ptrs to the server
	function sendPtr(info){
		console.log(info);
		clientSrv.write(info);
	}

	// When the webview is closed
	panel.onDidDispose(
		()=>{
			clearInterval(dataRetrive);
			clientLib.end();
			clientSrv.end();
			console.log("loop exited");
				
		},
		null,
		context.subscriptions
	);

	});

	context.subscriptions.push(disposable);
	context.subscriptions.push(init);

}
exports.activate = activate;

// this method is called when your extension is deactivated
function deactivate() {}

module.exports = {
	activate,
	deactivate
}
