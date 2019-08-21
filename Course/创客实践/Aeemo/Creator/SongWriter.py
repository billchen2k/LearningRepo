import pygame
import time
scoreDataA = []
scoreDataB = []
scoreDataC = []
scoreDataD = []


def saveFile():
    index = input("Enter your song INDEX:")
    with open("SongData.h", "w+") as f:
        f.writelines("const int LENGTH_" + str(index) +  " = " + str(len(scoreDataA)) + ";")
        f.write("static const bool ScoreData_" + str(index) + "[4][" + str(len(scoreDataA)) + "] PROGMEM = {" + 
			str(scoreDataA).replace('[', '{').replace(']', '}') + ",\n" + 
			str(scoreDataB).replace('[', '{').replace(']', '}') + ",\n" +
			str(scoreDataC).replace('[', '{').replace(']', '}') + ",\n" +
			str(scoreDataD).replace('[', '{').replace(']', '}') + "\n};")


def appender(keys, target, store):
    if(keys[target]):
        store.append(1)
    else:
        store.append(0)


def main():
    print("Now we are starting creating songs.")
    print(
        "Key [A] [S] [D] [F] represents four keys on the keyboard. [Enter] to end.")
    input(" Please do this in the pygame window, or we won't be able to detect keyboard events. Press any key to start.\n")
    pygame.init()
    screen = pygame.display.set_mode((640, 480))
    pygame.display.set_caption('Song Creator')
    while(1):
        keys = pygame.key.get_pressed()
        appender(keys, pygame.K_a, scoreDataA)
        appender(keys, pygame.K_s, scoreDataB)
        appender(keys, pygame.K_d, scoreDataC)
        appender(keys, pygame.K_f, scoreDataD)
        print(str(keys[pygame.K_a]) + str(keys[pygame.K_s]) +
              str(keys[pygame.K_d]) + str(keys[pygame.K_f]))
        time.sleep(0.1)
        if(keys[pygame.K_RETURN]):
            pygame.quit()
            break
        pygame.event.pump()
    print(scoreDataA)
    print(scoreDataB)
    print(scoreDataC)
    print(scoreDataD)
    saveFile()
    input("End. Song length: " + str(len(scoreDataA)))


main()
