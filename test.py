import tkinter
import time

PIXEL = 20
SIZEX = 60
SIZEY = 40

TIMER = 0.001

MIX = 1

PIXELS = [[0 for i in range(SIZEX)] for j in range(SIZEY)]
TEXTS = [[0 for i in range(SIZEX)] for j in range(SIZEY)]

def screen_test_init(myCanvas):
    global MIX

    for y in range(SIZEY):
        for x in range(SIZEX):
            PIXELS[y][x] = myCanvas.create_rectangle(x*PIXEL, y*PIXEL,(x+1)*PIXEL, (y+1)*PIXEL, outline="#fff", fill=f"#fff")

    for y in range(SIZEY):
        for x in range(SIZEX):
            TEXTS[y][x] = myCanvas.create_text((x)*PIXEL+5, (y)*PIXEL+5, text=chr(MIX%219+36), font="Helvetica 12", fill=f"#fff")
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
            myCanvas.itemconfig(PIXELS[y][x], fill=f"#{(x+MIX)%10}{(y+MIX)%10}0")
            txt = ord(myCanvas.itemcget(TEXTS[y][x], 'text')[0])
            myCanvas.itemconfig(TEXTS[y][x], text=chr((txt+MIX)%219+36))
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
    myCanvas.update()

    old_y_size = myCanvas.winfo_height() - 4
    old_x_size = myCanvas.winfo_width() - 4


    while True:
        MIX += 1

        new_y_size = myCanvas.winfo_height() - 4
        new_x_size = myCanvas.winfo_width() - 4

        screen_main(myCanvas)
        #myCanvas.config(width=myCanvas.winfo_height(),height=myCanvas.winfo_width())

        myCanvas.scale("all", 0, 0, new_x_size / old_x_size, new_y_size / old_y_size)

        myCanvas.update()

        old_y_size = new_y_size
        old_x_size = new_x_size

        time.sleep(TIMER)

    return

if __name__ == "__main__":
    main()

