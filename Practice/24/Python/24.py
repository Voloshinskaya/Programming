import json
def json_task():

with open("in.json", "r") as read_file:
in_file = json.load(read_file)
out=[]
userid=-1
for i in in_file:
if i['userId']!=userid:
if userid!=-1:
out.append(one_record)

userid=i['userId']
one_record={'task_completed':0, 'userId':userid}
if i['completed']:
one_record['task_completed']+=1
out.append(one_record)

with open("out.json", "w") as write_file:
json.dump(out, write_file)
