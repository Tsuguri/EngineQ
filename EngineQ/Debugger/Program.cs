using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Mono.Debugger.Soft;

namespace Debugger
{
	class Program
	{
		static void Main(string[] args)
		{
			Console.WriteLine("Connecting");

			var vm = VirtualMachineManager.Connect(new System.Net.IPEndPoint(System.Net.IPAddress.Loopback, 56000));

			if (vm == null)
				Console.WriteLine("Cannot connect to app");
			else
				Console.WriteLine("Connected");

			foreach (var th in vm.GetThreads())
				vm.CreateStepRequest(th);

		//	vm.CreateAssemblyLoadRequest();
			System.Threading.Thread.Sleep(2000);

			Console.WriteLine("Resuming");
		//	vm.Resume();
		//	vm.Suspend();

			//	var types = vm.GetTypesForSourceFile("Script.cs", true);

			var types = vm.GetTypes("CameraMoveClass.cs", true);

			foreach(var type in types)
			{
				Console.WriteLine($"{type.FullName}");
			}

		//	var method = types[0].GetMethod("ToggleEnableSkullScriptAction");


		//	var bp = vm.SetBreakpoint(method, 0);

			

		//	Console.WriteLine("Breakpoint set");

		//	var locals = method.GetLocals();

			while(true)
			{
				var evset = vm.GetNextEventSet();
				
				if(evset.Events.Length > 0)
				{
					Console.WriteLine($"Recieved {evset.Events.Length} events");
					foreach(var ev in evset.Events)
						Console.WriteLine($"\t{ev}");
				}
			}
		}
	}
}
