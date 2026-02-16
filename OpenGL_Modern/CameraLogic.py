import BwtEngine

def update_camera(cam):
    vitesse = 0.001
    mouvement = BwtEngine.Vector3(0, vitesse, 0)
    
    cam.Move(mouvement)
    
    print("--> Python est en train de faire monter la camera !")