import json

with open( "in.json", "r" ) as inFile:
    inData = json.load( inFile )

outData = []

for record in inData:

    if len( outData ) == 0:
        outData += [ {'task_completed':0, 'userId':record[ 'userId' ] } ]

    elif outData[ -1 ][ 'userId' ] != record[ 'userId' ]:
        outData += [ { 'task_completed' : 0, 'userId' : record[ 'userId' ] } ]

    outData[ len(outData) - 1 ][ 'task_completed' ] += record[ 'completed' ]

with open( "out.json", "w" ) as outFile:
    json.dump( outData, outFile )
