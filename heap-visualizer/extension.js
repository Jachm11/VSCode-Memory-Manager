// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require('vscode');

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
			{}
		);
		
		const loop = ()=>{
			console.log("hola");
			
		}
		vscode.window.showInformationMessage('Heap Visualizer initialized!');
		const interval = setInterval(loop , 1000);
		panel.onDidDispose(
			()=>{
				clearInterval(interval);
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
