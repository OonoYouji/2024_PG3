using ONEngine;
using System;
using System.Diagnostics;
public class Player : ScriptComponent {

	public override void Initialize() {
		Console.WriteLine("Player.Init() called!");
		nativeEntityId = 0; // Initialize the native entity ID
								   //int id = EntityId;
	}

	public override void Update() {
		//if (transform == null) {
		//	Console.WriteLine("Transform is null, cannot update position.");
		//	return;
		//}

		Transform t = transform; // Get the current transform
		t.position.x += 1.0f; // Increment the x position by 1.0
		transform = t; // Update the transform with the new position

		//Console.WriteLine("Player position updated.");
		Debug.WriteLine($"Player position updated to: ({t.position.x}, {t.position.y}, {t.position.z})");
	}


}
