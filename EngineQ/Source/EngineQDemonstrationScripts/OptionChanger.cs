using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public class OptionChanger : Script
	{
		public abstract class BaseOption
		{
			public abstract void Changed(int value);

			public abstract string Name { get; }
			public abstract string Value { get; }
		}

		public class GenericOption<TType> : BaseOption
		{
			public delegate TType ChangedHandler(TType value, int direction);

			private string name;
			private TType value;
			private ChangedHandler handler;

			public GenericOption(string name, ChangedHandler handler, TType value = default(TType))
			{
				this.name = name;
				this.handler = handler;
				this.value = value;
			}

			public override void Changed(int direction)
			{
				this.handler(this.value, direction);
			}

			public override string Name
			{
				get
				{
					return this.name;
				}
			}

			public override string Value
			{
				get
				{
					return this.value.ToString();
				}
			}
		}

		public void RegisterOption<TType>(string name, GenericOption<TType>.ChangedHandler handler, TType value = default(TType))
		{
			this.options.Add(new GenericOption<TType>(name, handler, value));
		}

		private List<BaseOption> options = new List<BaseOption>();
		private int currentOption = 0;

		protected override void OnEnable()
		{
			Input.RegisterKeyEvent(Input.Key.Kp4, ChangedOptionAnction);
			Input.RegisterKeyEvent(Input.Key.Kp6, ChangedOptionAnction);
			Input.RegisterKeyEvent(Input.Key.Kp8, ChangedOptionValueAction);
			Input.RegisterKeyEvent(Input.Key.Kp2, ChangedOptionValueAction);
			Input.RegisterKeyEvent(Input.Key.Kp5, CurrentOptionAction);
		}

		protected override void OnDeactivate()
		{
			Input.DeregisterKeyEvent(Input.Key.Kp4, ChangedOptionAnction);
			Input.DeregisterKeyEvent(Input.Key.Kp6, ChangedOptionAnction);
			Input.DeregisterKeyEvent(Input.Key.Kp8, ChangedOptionValueAction);
			Input.DeregisterKeyEvent(Input.Key.Kp2, ChangedOptionValueAction);
			Input.DeregisterKeyEvent(Input.Key.Kp5, CurrentOptionAction);
		}
		
		private void CurrentOptionAction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Press)
				return;

			if (options.Count == 0)
				return;

			Console.WriteLine($"Current option: {options[currentOption].Name} = {options[currentOption].Value}");
		}

		private void ChangedOptionValueAction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Press)
				return;

			if (options.Count == 0)
				return;

			if (key == Input.Key.Kp8)
				options[currentOption].Changed(1);
			if (key == Input.Key.Kp2)
				options[currentOption].Changed(-1);

			Console.WriteLine($"{options[currentOption].Name} set to {options[currentOption].Value}");
		}

		private void ChangedOptionAnction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Press)
				return;

			if (options.Count == 0)
			{
				Console.WriteLine("<No options>");
				return;
			}

			if (key == Input.Key.Kp4)
				currentOption = (currentOption + 1) % options.Count;
			if (key == Input.Key.Kp6)
				currentOption = (currentOption + options.Count - 1) % options.Count;

			Console.WriteLine($"Selected option: {options[currentOption].Name}");
		}
	}
}
