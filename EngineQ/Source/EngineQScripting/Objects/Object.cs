using System;
using System.Collections.Generic;

namespace EngineQ
{
	/// <summary>
	/// Base class for all objects used natively by the Engine.
	/// </summary>
	public abstract class Object
	{
		private IntPtr nativeHandle;

		/// <summary>
		/// Handle to the native representation of the object.
		/// </summary>
		/// <exception cref="NullReferenceException">
		/// Throws when used on destroyed object.
		/// </exception>
		protected IntPtr NativeHandle
		{
			get
			{
				if (nativeHandle == IntPtr.Zero)
					throw new NullReferenceException("Attempt to use destroyed object");

				return nativeHandle;
			}
		}

		/// <summary>
		/// Says if object is not removed from the Engine.
		/// If false, the object is destroyed and cannot be used. Destroyed object behaves as null reference.
		/// </summary>
		/// <value>
		/// If true, then object can be used.
		/// If false, then object was destroyed and usage will throw <see cref="NullReferenceException"/>. 
		/// </value>
		/// <example>
		/// This example shows how to use <see cref="IsAlive"/> property. 
		/// <code>
		/// <see cref="Object"/> obj;
		/// 
		/// // Set obj reference to some object
		/// 
		/// if (obj.IsAlive)
		/// {
		///		// It is ok to use object
		///		obj.Method();
		///	}
		///	else
		///	{
		///		// Usage of object will throw <see cref="NullReferenceException"/>
		///		obj.Method(); // Throws
		///	}
		/// </code>
		/// </example>
		public bool IsAlive
		{
			get
			{
				return this.nativeHandle != IntPtr.Zero;
			}
		}

		// TMP
		private static Dictionary<Type, int> typesCount = new Dictionary<Type, int>();

		private static int objectsCount = 0;
		private static int maxObjectsCount = 0;
		private int objectIndex = -1;

		internal Object()
		{
			// TMP
			objectsCount += 1;
			maxObjectsCount += 1;
			if (objectIndex != -1)
				Console.WriteLine($"SE: !!!!! ALREADY CREATED !!!!!");

			int objTotal = 0;
			if (typesCount.ContainsKey(GetType()))
			{
				objTotal = typesCount[GetType()] += 1;
			}
			else
			{
				typesCount.Add(GetType(), 1);
				objTotal = 1;
			}

			this.objectIndex = maxObjectsCount;
			Console.WriteLine($"SE: [{objectIndex,3}|{objectsCount,3}] Constructed {GetType()} ({objTotal} in total) with handle {nativeHandle}");
		}

		// TMP
		~Object()
		{
			if (objectIndex == -1)
				Console.WriteLine($"SE: !!!!! ALREADY DESTROYED !!!!!");

			int objTotal = typesCount[GetType()] -= 1;

			objectsCount -= 1;
			Console.WriteLine($"SE: [{objectIndex,3}|{objectsCount,3}] Destructed {GetType()} ({objTotal} left) with handle {nativeHandle}");

		//	Console.Write("Left: ");
		//	foreach (var pair in typesCount)
		//		if (pair.Value != 0)
		//			Console.Write($"({pair.Key},{pair.Value})");
		//	Console.WriteLine();

			this.objectIndex = -1;
		}

		/// <summary>
		/// Determines whether object is the same object as current instance.
		/// Destroyed objects behave as null reference.
		/// </summary>
		/// <param name="obj">Object to be compared with current instance.</param>
		/// <returns>True if the objects are equal.</returns>
		public override bool Equals(object obj)
		{
			if (obj == null)
				return this.nativeHandle == IntPtr.Zero;

			if (this.GetType() != obj.GetType())
				return false;

			return this.nativeHandle == ((EngineQ.Object)obj).nativeHandle;
		}

		/// <summary>
		/// Default hash function.
		/// </summary>
		/// <returns>Default hash code.</returns>
		public override int GetHashCode()
		{
			return base.GetHashCode();
		}

		/// <summary>
		/// Determines whether two objects are the same objects.
		/// Destroyed objects behave as null reference.
		/// </summary>
		/// <param name="obj1">First object to be checked.</param>
		/// <param name="obj2">Second object to be checked.</param>
		/// <returns>True if objects are equal.</returns>
		public static bool operator ==(EngineQ.Object obj1, EngineQ.Object obj2)
		{
			if (!ReferenceEquals(obj1, null))
				return obj1.Equals(obj2);

			if (ReferenceEquals(obj2, null))
				return true;

			return obj2.nativeHandle == IntPtr.Zero;
		}

		/// <summary>
		/// Determines whether two objects are not the same objects.
		/// Destroyed objects behave as null reference.
		/// </summary>
		/// <param name="obj1">First object to be checked.</param>
		/// <param name="obj2">Second object to be checked.</param>
		/// <returns>True if objects are not equal.</returns>
		public static bool operator !=(EngineQ.Object obj1, EngineQ.Object obj2)
		{
			return !(obj1 == obj2);
		}
	}
}
