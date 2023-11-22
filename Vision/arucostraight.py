import math
import cv2 as cv
import numpy as np
import json


class staticvariables:

    extremiteupleft = None
    extremitedownleft = None
    extremitedownright = None
    extremiteupright = None


def checkcerise(centre, img):
    threshhold = 50
    ceriseplace = img[centre[1]-10:centre[1]+10,
                      centre[0]-10:centre[0]+10]
    red_lower1 = np.array([0, 0, 120], np.uint8)
    red_upper1 = np.array([70, 90, 200], np.uint8)
    red_mask1 = cv.inRange(ceriseplace, red_lower1, red_upper1)

    density = np.sum(red_mask1, axis=(0, 1))/255
    print('density')
    print(ceriseplace)
    print(density)


    if (density > threshhold):
        return True
    else:
        return False


def roundnumbers(res):
    for key, value in res.items():
        for i in res[key]:
            i['centre'][0] = round(i['centre'][0])
            i['centre'][1] = round(i['centre'][1])


def chiffreCoordonnee(x, y):
    return [int(round(x // 255)), int(round(x % 255)), int(round(y // 255)), int(round(y % 255))]


def checkOverlap(R,  firstcorner, secondcorner, centergateau):
    Xc = centergateau[0]
    Yc = centergateau[1]
    X1 = firstcorner[0]
    Y1 = firstcorner[1]
    X2 = secondcorner[0]
    Y2 = secondcorner[1]

    Xn = max(X1, min(Xc, X2))
    Yn = max(Y1, min(Yc, Y2))
    Dx = Xn - Xc
    Dy = Yn - Yc
    return (Dx * Dx + Dy * Dy) <= R * R




def couleur(id):
    if (id == 47):
        return 1
    if (id == 13):
        return 2
    if (id == 36):
        return 3


def getvuededessus(img, pointupleft, pointupright, pointdownleft, pointdownright, resPos):
    pts1 = np.float32([pointupleft, pointupright,
                      pointdownleft, pointdownright])
 #   pts2 = np.float32([[525, 1480, ], [2475, 1480],
  #                    [525, 520], [2475, 520]])
    pts2 = np.float32([[520, 525], [1480, 525], [520, 2475], [1480, 2475]])
    M = cv.getPerspectiveTransform(pts1, pts2)
    
    dst = cv.warpPerspective(img, M, (2000, 3000))
    resPos1 = []
    for i in resPos:
        location = []
        for point in i:
            # Apply the perspective transform on the single point
            transformed_point = cv.perspectiveTransform(
                point.reshape(-1, 1, 2), M)
            location.append(transformed_point[0][0])
        resPos1.append(location)
    return dst, resPos1


def calculatecenetofmultiplegateau(pos, id, dst):

    if (id == 47 or id == 13 or id == 36):
        return calculatecenterofgateau(pos[0], pos[1], pos[2], pos[3], dst)
    else:
        return (-1, -1)


def calculatecenterofqr(point1, point2):
    return ((point1[0]+point2[0])/2, (point1[1]+point2[1])/2)


def calculatecenterofgateau(point1, point2, point3, point4, dst):

    x1 = point1[0]
    y1 = point1[1]
    x2 = point2[0]
    y2 = point2[1]
    x3 = point3[0]
    y3 = point3[1]
    x4 = point4[0]
    y4 = point4[1]

    coef = calculatedistancebetween2points(point1, point2)/50
    a = 28.5*coef

    pts1 = np.float32([point1, point2,
                       point3])
    pts2 = np.float32([[0, 0], [50*coef, 0], [50*coef, 50*coef], ])
    M = cv.getAffineTransform(pts2, pts1)
    x, y = np.dot(M, (25*coef, -a, 1))

    #cv.circle(dst, (int(x), int(y)), 5, (255, 0, 0), 5)
    return (x, y)


def calculateextremite(aruco, resIds, resPos, side):
    if (resIds.__contains__(aruco)):
        point = resPos[resIds.index(aruco)][side]

        return [int(x) for x in point]


def calculatedistancebetween2points(point1, point2):
    return math.sqrt(math.pow(point1[0]-point2[0], 2)+math.pow(point1[1]-point2[1], 2))


def arucodetection(img, marker_size=4, total_markers=250, draw=True):
    gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
    key = getattr(
        cv.aruco, f'DICT_{marker_size}X{marker_size}_{total_markers}')
    arucoDict = cv.aruco.Dictionary_get(key)
    arucoParam = cv.aruco.DetectorParameters_create()
    bbox, ids, _ = cv.aruco.detectMarkers(
        gray, arucoDict, parameters=arucoParam)
    resPos = []
    resIds = []

    j = 0

    for i in bbox:
        j = j+1
        if (cv.contourArea(i) > 0):
            resPos.append(i[0])
            resIds.append(ids[j-1][0])

    if (draw):

        for i in resPos:

            # print(i)

            for j in range(len(i)):
                f = tuple([int(x) for x in i[j]])
                if (j == 3):
                    g = tuple([int(x) for x in i[0]])
                else:
                    g = tuple([int(x) for x in i[j+1]])

                cv.circle(img, f, 1, (0, 0, 255), 5)

                cv.line(img, f, g, (255, 0, 0), 5)
    return (resPos, resIds)


def checkPointEgal(point1, point2):
    return ((math.fabs(round(point1[0]) - round(point2[0]))) < 10) and (math.fabs((round(point1[1]) - round(point2[1]))) < 10)


def combinePos(resPos1, resPos2, resIds1, resIds2):
    resPosfinal = resPos2.copy()
    resIdsfinal = resIds2.copy()

       
    for i in range(resPos1.__len__()):
        exist = False

        for j in range(resPos2.__len__()):
            if (checkPointEgal(resPos1[i][0], resPos2[j][0]) and checkPointEgal(resPos1[i][1], resPos2[j][1]) and checkPointEgal(resPos1[i][2], resPos2[j][2]) and checkPointEgal(resPos1[i][3], resPos2[j][3])):
                exist = True
        if (not (exist)):

            resPosfinal.append(resPos1[i])
            resIdsfinal.append(resIds1[i])

    return resPosfinal, resIdsfinal




def findAruco(img, marker_size=4, total_markers=250, draw=True):

    resPos, resIds = arucodetection(img, draw=True)
    # downright
    arucoIddownright = 23
    if (calculateextremite(
            arucoIddownright, resIds, resPos, 2) != None):
        staticvariables.extremitedownright = calculateextremite(
            arucoIddownright, resIds, resPos, 2)

    # downleft
    arucoIddownleft = 22
    if (calculateextremite(
            arucoIddownleft, resIds, resPos, 3) != None):
        staticvariables.extremitedownleft = calculateextremite(
            arucoIddownleft, resIds, resPos, 3)

    # upright
    arucoIdupright = 21
    if (calculateextremite(
            arucoIdupright, resIds, resPos, 1) != None):
        staticvariables.extremiteupright = calculateextremite(
            arucoIdupright, resIds, resPos, 1)

    # upleft
    arucoIdupleft = 20
    if (calculateextremite(
            arucoIdupleft, resIds, resPos, 0) != None):
        staticvariables.extremiteupleft = calculateextremite(
            arucoIdupleft, resIds, resPos, 0)

    if ((staticvariables.extremiteupleft != None) and (staticvariables.extremiteupright != None) and (staticvariables.extremitedownleft != None) and (staticvariables.extremitedownright != None)):

        dst, resPos1 = getvuededessus(img, staticvariables.extremiteupleft, staticvariables.extremiteupright,
                                      staticvariables.extremitedownleft, staticvariables.extremitedownright, resPos)
        
        # apply filters here
        #dst = cv.GaussianBlur(dst, (5, 5), 0)

        #dst = cv.erode(dst, kernel, iterations=1)
        #dst = cv.dilate(dst, kernel, iterations=1)

        resPos2, resIds2 = arucodetection(dst,)
        resPos, resIds = combinePos(resPos1, resPos2, resIds, resIds2)

    else:
        dst = img

        print({'error': "cant calculate the cakes' positions"})
        return img
    if (1):
        tableaufinal = []
        res = {}
        foundvert = False
        foundbleu = False
        res['gateaux'] = []
        for i in range(resPos.__len__()):
            if ((resIds[i] >= 1) and (resIds[i] <= 5)):
                t, z = calculatecenterofqr(
                    resPos[i][0], resPos[i][2])
                res["equipe bleue"] = (t, z)
                tableaufinal.append([chiffreCoordonnee(t, z), 0])
                foundbleu = True

            if ((resIds[i] >= 6) and (resIds[i] <= 10)):
                t, z = calculatecenterofqr(
                    resPos[i][0], resPos[i][2])
                res["equipe verte"] = (t, z)
                tableaufinal.append([chiffreCoordonnee(t, z), 1])
                foundvert = True

        if foundbleu == False:
            res["equipe bleue"] = (-1, -1)
            tableaufinal.append([-1, -1, 0])
        if foundvert == False:
            res["equipe verte"] = (-1, -1)
            tableaufinal.append([-1, -1, 1])

        for i in range(resPos.__len__()):

            t, z = calculatecenterofqr(
                resPos[i][0], resPos[i][2])

            x, y = calculatecenetofmultiplegateau(resPos[i], resIds[i], dst)
            if (resIds[i] == 47 or resIds[i] == 13 or resIds[i] == 36):
                tableaufinal.append(
                    [chiffreCoordonnee(x, y)[0], chiffreCoordonnee(x, y)[1], couleur(resIds[i])+checkcerise((round(x), round(y)), dst)])
                res['gateaux'].append({'centre': [x, y],
                                       'couleur': couleur(resIds[i]),
                                       
                                       'cerise': checkcerise((round(x), round(y)), dst)})
        l = []
        for i in range(len(tableaufinal)):  # Traversing through the main list
            # Traversing through each sublist

            for j in range(len(tableaufinal[i])):

                l.append(tableaufinal[i][j])
        print(l)
        print(res)
        return dst

'''

img = cv.imread("C://Users//Admin//Desktop//VCSpython//yyy.jpeg")
# finding aruco tag from photo
# resizing affects aruco detection

#img = cv.resize(img, None, fx=3, fy=3)
#img = cv.GaussianBlur(img, (5, 5), 0)

dst = findAruco(img=img)

cv.imshow("aruco", dst)
#cv.imshow("gateau", dst)
cv.imwrite("C://Users//Admin//Desktop//VCSpython//testaruco.png", img)
cv.waitKey(0)
'''
'''
# fndiing aruco tag from video
import time


# Initialize the Picamera and numpy array
with picamera.PiCamera() as camera:
    camera.resolution = (2400, 2400)
    camera.framerate=5
    with picamera.array.PiRGBArray(camera) as output:
        # Allow the camera to warm up
        #camera.start_preview()
        time.sleep(2)

        # Capture an image from the camera and process it with OpenCV
        camera.capture(output, format="bgr")
        image = output.array

        dst=findAruco(img=image)
        dst = cv.resize(dst,(800,800))
        cv.imshow('Gray Image', dst)
        cv.waitKey(0)
'''
import cv2
import numpy as np
import picamera
import picamera.array
import time
# Initialize the Picamera and numpy array
with picamera.PiCamera() as camera:
    camera.resolution = (2432, 2432)
    camera.framerate = 5
    with picamera.array.PiRGBArray(camera) as output:
        # Allow the camera to warm up
        #camera.start_preview()
        #time.sleep(2)

        # Continuously capture and process video frames
        for frame in camera.capture_continuous(output, format="bgr", use_video_port=True):
            # Get the numpy array representing the image
            image = frame.array
            
            # Process the image with OpenCV
            dst = findAruco(img=image)
            dst = cv.resize(dst,(1000,1000))
            cv.imshow("aruco", dst)

            
            
            
            # Clear the output buffer for the next capture
            output.truncate(0)
            
            # Exit the program if the "q" key is pressed
            if cv2.waitKey(1) & 0xFF == ord('q'):
                break

# Release the video stream and close all windows
cv2.destroyAllWindows()


'''
while (1):
    _, frame = cam.read()
    findAruco(frame)

    cv.imshow('aruco', frame)

    k = cv.waitKey(10)
    if k == ord('q'):
        break
cam.release()
'''
cv.destroyAllWindows()
