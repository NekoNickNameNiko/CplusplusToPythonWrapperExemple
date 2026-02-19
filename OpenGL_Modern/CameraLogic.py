import BwtEngine

def update_camera(cam, deltaTime):
    speed : float = 5 * deltaTime
    rotationSpeed : float = 3 * deltaTime

    if(BwtEngine.IsKeyDown(BwtEngine.Key_W)):
        mouvement : BwtEngine.Vector3 = BwtEngine.Vector3(0, 0, -speed)
        cam.Move(mouvement)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_S)):
        mouvement : BwtEngine.Vector3 = BwtEngine.Vector3(0, 0, speed)
        cam.Move(mouvement)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_A)):
        mouvement : BwtEngine.Vector3 = BwtEngine.Vector3(-speed, 0, 0)
        cam.Move(mouvement)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_D)):
        mouvement : BwtEngine.Vector3 = BwtEngine.Vector3(speed, 0, 0)
        cam.Move(mouvement)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_Q)):
        mouvement : BwtEngine.Vector3 = BwtEngine.Vector3(0, -speed, 0)
        cam.Move(mouvement)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_E)):
        mouvement : BwtEngine.Vector3 = BwtEngine.Vector3(0, speed, 0)
        cam.Move(mouvement)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_Z)):
        rotation : BwtEngine.Vector3 = BwtEngine.Vector3(0, rotationSpeed, 0)
        cam.Rotate(rotation)

    if(BwtEngine.IsKeyDown(BwtEngine.Key_X)):
        rotation : BwtEngine.Vector3 = BwtEngine.Vector3(0, -rotationSpeed, 0)
        cam.Rotate(rotation)
