using System;

namespace EngineQ
{
	public abstract class Object
	{
		private IntPtr nativeHandle;
		protected IntPtr NativeHandle
		{
			get
			{
				if (nativeHandle == IntPtr.Zero)
					throw new NullReferenceException("Attempt to use destroyed object");

				return nativeHandle;
			}
		}

		public bool IsAlive
		{
			get
			{
				return this.nativeHandle != IntPtr.Zero;
			}
		}

		internal Object()
		{
			// TMP
			Console.WriteLine($"SE: Constructed {GetType()} with handle {nativeHandle}");
		}

		// TMP
		~Object()
		{
			Console.WriteLine($"SE: Destructed {GetType()} with handle {nativeHandle}");
		}

		public override bool Equals(object obj)
		{
			if (obj == null)
				return this.nativeHandle == IntPtr.Zero;

			if (this.GetType() != obj.GetType())
				return false;
			
			return this.nativeHandle == ((EngineQ.Object)obj).nativeHandle;
		}

		public override int GetHashCode()
		{
			return base.GetHashCode();
		}
		
		public static bool operator ==(EngineQ.Object obj1, EngineQ.Object obj2)
		{
			if (!ReferenceEquals(obj1, null))
				return obj1.Equals(obj2);

			if (ReferenceEquals(obj2, null))
				return true;

			return obj2.nativeHandle == IntPtr.Zero;
		}

		public static bool operator !=(EngineQ.Object obj1, EngineQ.Object obj2)
		{
			return !(obj1 == obj2);
		}
	}
}
