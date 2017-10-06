using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;

namespace QScripts
{
	public abstract class BaseOption
	{
		public abstract void Changed(int direction);

		public abstract string Name { get; }
		public abstract string Value { get; }
	}

	public class GenericOption<TType> : BaseOption
	{
		public delegate void ChangedHandler(ref TType value, int direction);

		private readonly string name;
		private readonly ChangedHandler handler;
		private TType value;

		public GenericOption(string name, ChangedHandler handler, TType value = default(TType))
		{
			this.name = name;
			this.handler = handler;
			this.value = value;
		}

		public override void Changed(int direction)
		{
			this.handler(ref this.value, direction);
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

	public class SimpleFloatOption : BaseOption
	{
		public delegate void ChangedHandler(float value);

		private readonly string name;
		private float value;

		private readonly float minValue;
		private readonly float maxValue;
		private readonly float step;

		private readonly ChangedHandler handler;

		public SimpleFloatOption(string name, float value, float minValue, float maxValue, float step, ChangedHandler handler)
		{
			this.name = name;
			this.value = value;
			this.minValue = minValue;
			this.maxValue = maxValue;
			this.step = step;
			this.handler = handler;
		}

		public override void Changed(int direction)
		{
			this.value += step * direction;

			if (this.value < minValue)
				this.value = minValue;
			if (this.value > maxValue)
				this.value = maxValue;

			this.handler(value);
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

	public class SimpleIntOption : BaseOption
	{
		public delegate void ChangedHandler(int value);

		private readonly string name;
		private int value;

		private readonly int minValue;
		private readonly int maxValue;
		private readonly int step;

		private readonly ChangedHandler handler;

		public SimpleIntOption(string name, int value, int minValue, int maxValue, int step, ChangedHandler handler)
		{
			this.name = name;
			this.value = value;
			this.minValue = minValue;
			this.maxValue = maxValue;
			this.step = step;
			this.handler = handler;
		}

		public override void Changed(int direction)
		{
			this.value += step * direction;

			if (this.value < minValue)
				this.value = minValue;
			if (this.value > maxValue)
				this.value = maxValue;

			this.handler(value);
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

	public class SimpleBoolOption : BaseOption
	{
		public delegate void ChangedHandler(bool value);

		private readonly string name;
		private readonly bool toggle;
		private bool value;

		private readonly ChangedHandler handler;

		public SimpleBoolOption(string name, bool value, ChangedHandler handler, bool toggle = true)
		{
			this.name = name;
			this.value = value;
			this.toggle = toggle;
			this.handler = handler;
		}

		public override void Changed(int direction)
		{
			if (direction != 0 && toggle)
			{
				this.value = !this.value;
			}
			else
			{
				if (direction < 0)
					this.value = false;
				if (direction > 0)
					this.value = true;
			}

			this.handler(value);
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

	public class OptionChanger : Script
	{
		public void AddOption(BaseOption option, bool trigger = true)
		{
			this.options.Add(option);

			if (trigger)
				option.Changed(0);

			this.options.Sort((BaseOption o1, BaseOption o2) => o2.Name.CompareTo(o1.Name));
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
			if (action != Input.KeyAction.Press && action != Input.KeyAction.Repeat)
				return;

			if (options.Count == 0)
				return;

			int value = 1;
			if (Input.IsKeyPressed(Input.Key.LeftShift))
				value = 3;

			if (key == Input.Key.Kp8)
				options[currentOption].Changed(value);
			if (key == Input.Key.Kp2)
				options[currentOption].Changed(-value);

			Console.WriteLine($"{options[currentOption].Name} = {options[currentOption].Value}");
		}

		private void ChangedOptionAnction(Input.Key key, Input.KeyAction action)
		{
			if (action != Input.KeyAction.Press && action != Input.KeyAction.Repeat)
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

			Console.WriteLine($"Selected option: {options[currentOption].Name} = {options[currentOption].Value}");
		}
	}
}
