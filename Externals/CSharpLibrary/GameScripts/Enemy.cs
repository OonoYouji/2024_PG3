using ONEngine;
using System;

public class Enemy : ScriptComponent {

	public override void Initialize() {
		Console.WriteLine("Enemy.Init() called!");
	}

	public override void Update() {

		//if (transform == null) {
		//	Console.WriteLine("Transform is null, cannot update position.");
		//	return;
		//}

		Transform t = transform; // Get the current transform
		t.position.x += 1.0f; // Increment the x position by 1.0
		transform = t; // Update the transform with the new position

		Console.WriteLine($"Enemy position updated to: ({t.position.x}, {t.position.y}, {t.position.z})");
		Console.WriteLine("Enemy.Update() called!");
	}
}