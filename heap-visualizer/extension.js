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

		const panel = vscode.window.createWebviewPanel(
			'HS',
			'Heap Visualizer',
			vscode.ViewColumn.One,
			{
				enableScripts: true
			}
		);

		//let iteration = 0;
		//const loop = ()=>{
			//const msg = iteration++ % 2 ? '19' : '2';
        	//panel.webview.html = getWebviewContent(msg);
		//}

		//const interval = setInterval(loop , 5000);

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
				<p>Direcciones de memoria por dato:<br>${dirs}</p>
				<p></p>
				<button style="background-color:#007bcd; border-color:#007bcd; color:white">Connect to server</button>
			</body>
			</html>`;
		}


		vscode.window.showInformationMessage('Heap Visualizer initialized!');
		panel.onDidDispose(
			()=>{
				//clearInterval(interval);
				clearInterval(dataRetrive);
				client.end();
				console.log("loop exited");
				
			},
			null,
			context.subscriptions
		);

		const client = net.createConnection({port:54000},()=>{
			if ( !client.address){
				console.log("Failed to connect")
			}else{
				client.write('1');
				console.log('Connected yay!')
			}
		});

		client.on('data',(data)=>{
			//console.log(data.toString());
			console.log(parseData(data.toString()));
		});
		client.on('end',()=>{
			console.log('Disconneted!');
			});


		const getData= ()=>{
			client.write('1');
		}

		const dataRetrive = setInterval(getData,3000);

	

		function parseData(info){
			var x = info.split(";");
			x = x.slice(0,(x.length)-1);
			var dir ="" ;
			var data = "";
			
			x.forEach(e => {
				var y = e.split(",");

				var bg = getRandomRgb();
				var dataSet;
				//labelsList.push(y[0]);

				dataSet = "{\nlabel:'"+y[1]+"',\ndata:["+y[3]+"],\nbackgroundColor:['"+bg+"'],\nborderColor:['"+bg+"'],\nborderWidth:1\n},";
				
				dir = dir + y[1] + ":" + y[2] + "<br>";

				console.log(y);
				console.log(dataSet);

				data = data + dataSet;
			});

			//console.log(data);
			//console.log(data.substring(0, data.length - 1));
			var labels = "'Heap Data'";
			//labelsList.forEach(e=>{
				//labels = labels + "'"+e+"',";
			//})
			
			panel.webview.html = getWebviewContent(labels,data.substring(0, data.length - 1),dir);

		}

		function getRandomRgb() {
			//var num = Math.round(0xffffff * Math.random());
			var r = 0;
			var g = 122;
			var b = 205;
			return 'rgb(' + r + ', ' + g + ', ' + b + ', 0.5'+ ')';
		  }


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
