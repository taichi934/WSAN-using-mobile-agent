# coding: UTF-8
import serial
import re
import time                   # timeが使えるように宣言
# Rcb4BaseLib.pyの中のRcb4BaseLibが使えるように設定
from Rcb4BaseLib import Rcb4BaseLib
import sys
sys.path.append('../Rcb4Lib')  # Rcb4Libの検索パスを追加


rcb4 = Rcb4BaseLib()      # rcb4をインスタンス(定義)

# rcb4.open('/dev/ttyAMA0',115200,1.3)  #(portName,bundrate,timeout(s))
# rcb4.open('/dev/ttyUSB0',115200,1.3)
if rcb4.open('COM3', 115200, 1.3) is False:
    print("cannot connect with rcb4...")
    rcb4.close()
    exit()
else:
    print("connect with rcb4 successfully")


# open port for dragino
serForDragino = serial.Serial("COM5", 9600)

if rcb4.checkAcknowledge() is True:  # 通信が返ってきたとき
    while True:
        data = serForDragino.readline().decode().strip()
        print(data)  # From node id = ooo  Recieved motion number o
        extractedNums = re.findall("[0-9]+", data)
        nodeId = extractedNums[0]
        recievedMotionNum = extractedNums[-1]   # 後ろから1番目の1桁以上の数字
        if recievedMotionNum == []:  # not recieve motion number
            break

        # モーション番号を再生
        # str -> int -> ascii文字 -> int
        recievedMotionNum = int(chr(int(recievedMotionNum)))
        print(f"MotionPlay({recievedMotionNum})")
        if rcb4.motionPlay(recievedMotionNum) is False:
            print(f"fale motion{recievedMotionNum}")

        while True:     # モーションの再生が終わるまで繰り返し
            currentMotionNum = rcb4.getMotionPlayNum()   # 現在再生されているモーション番号を取得
            if currentMotionNum < 0:                     # モーション番号が0より小さい場合はエラー
                print('motion get error', currentMotionNum)
                break
            if currentMotionNum == 0:                    # モーション番号が0のときは再生されていない状態
                print('stop motion or idle')
                break

            print('play motion -> ', currentMotionNum)
            time.sleep(0.1)

        # serForDragino.write(f"{nodeId}1")  # send back the result packet


else:  # 通信が返ってきていないときはエラー
    print('checkAcknowledge error')


rcb4.close()
