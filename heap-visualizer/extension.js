// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');
const net = require('net');

// this method is called when your extension is activated
// your extension is activated the very first time the command is executed

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


		let iteration = 0;
		const loop = ()=>{
			const msg = iteration++ % 2 ? '19' : '2';
        	panel.webview.html = getWebviewContent(msg);
		}

		const interval = setInterval(loop , 3000);

		function getWebviewContent(msg) {
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
                        labels: ['Red', 'Blue', 'Yellow', 'Green', 'Purple', 'Orange'],
                        datasets: [{
                            label: '# of Votes',
                            data: [[5,6], ${msg}, 3, 5, 2, 3],
                            backgroundColor: [
                                'rgba(255, 99, 132, 0.2)',
                                'rgba(54, 162, 235, 0.2)',
                                'rgba(255, 206, 86, 0.2)',
                                'rgba(75, 192, 192, 0.2)',
                                'rgba(153, 102, 255, 0.2)',
                                'rgba(255, 159, 64, 0.2)'
                            ],
                            borderColor: [
                                'rgba(255, 99, 132, 1)',
                                'rgba(54, 162, 235, 1)',
                                'rgba(255, 206, 86, 1)',
                                'rgba(75, 192, 192, 1)',
                                'rgba(153, 102, 255, 1)',
                                'rgba(255, 159, 64, 1)'
                            ],
                            borderWidth: 1
                        }]
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
                });</script>
			</body>
			</html>`;
		}


		vscode.window.showInformationMessage('Heap Visualizer initialized!');
		panel.onDidDispose(
			()=>{
				clearInterval(interval);
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

		console.log(client.address);

		client.on('data',(data)=>{
			console.log(data.toString());
		});
		client.on('end',()=>{
			console.log('Disconneted!');
			});



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
