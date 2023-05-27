import tkinter
import time

PIXEL = 10
SIZEX = 80
SIZEY = 60

TIMER = 0.01

MIX = 1

PIXELS = [[0 for i in range(SIZEX)] for j in range(SIZEY)]

def screen_test_init(myCanvas):
    global MIX

    for y in range(SIZEY):
        for x in range(SIZEX):
            PIXELS[y][x] = myCanvas.create_rectangle(x*PIXEL, y*PIXEL,(x+1)*PIXEL, (y+1)*PIXEL, outline="#fff", fill=f"#fff")

    for y in range(SIZEY):
        for x in range(SIZEX):
            myCanvas.create_text((x)*PIXEL+5, (y)*PIXEL+5, text=chr((MIX+36)%255), font="Helvetica 12", fill=f"#fff")
            MIX += 1
    #print(PIXELS)

    return

def screen_main_init(myCanvas):
    pass
    return

def screen_init(myCanvas):
    screen_test_init(myCanvas)
    # screen_main_init(myCanvas)
    return

def screen_test_main(myCanvas):
    for y in range(SIZEY):
        for x in range(SIZEX):
            #myCanvas.move(pixels[y][x],1*PIXEL,1*PIXEL)
            myCanvas.itemconfig(PIXELS[y][x], fill=f"#{(x+MIX)%10}{(y+MIX)%10}0")
    return

def screen_main_main(myCanvas):
    pass
    return

def screen_main(myCanvas):
    screen_test_main(myCanvas)
    # screen_main_main(myCanvas)
    return

def get_pixel():
    pass
    return

def main():
    global MIX

    root = tkinter.Tk()
    root.title("Grid And Boxes")
    myCanvas = tkinter.Canvas(root, bg="gray", height=SIZEY*PIXEL, width=SIZEX*PIXEL)
    myCanvas.pack(fill="both", expand=True)

    screen_init(myCanvas)

    while True:
        MIX += 1

        screen_main(myCanvas)

        myCanvas.update()
        time.sleep(TIMER)

    return

if __name__ == "__main__":
    main()

