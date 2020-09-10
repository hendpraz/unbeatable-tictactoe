import os
from flask import Flask, request, jsonify
from flask_cors import CORS
import requests
import json
from subprocess import Popen, PIPE

application = Flask(__name__, static_folder='../build', static_url_path='/')
CORS(application)

@application.route('/', methods=['POST'])
def process():
    fm = request.json["fm"]
    inp = request.json["inp"]
    state = request.json["state"]
    
    res = {}
    if validate(fm, inp, state):
        result = execute(fm, inp, state)
        if result[0] == 1:
            res["status"] = 500
        else:
            res["status"] = 200

        res["message"] = "OK"
        res["payload"] = { "condition": result[1], "state": result[2] }
    else:
        res["status"] = 400
        res["message"] = "Invalid request input"

    return jsonify(res)

def execute(fm, inp, state):
    # os.system("./prog {} {} {}".format(fm, inp, state))
    cmd = "./prog {} {} {}".format(fm, inp, state)

    p = Popen(cmd.split(), stdout=PIPE)

    i = 0
    max_i = 2
    outputs = []
    for line in iter(p.stdout.readline,""):
        if (i > max_i):
            break
        outputs.append(line.decode("utf-8"))
        i += 1
    
    separator = '|'
    result = []
    for otp in outputs:
        temp = otp.split(separator)
        result.append(temp[1])
    
    return result

def validate(fm, inp, state):
    valid = True
    if (fm != "y" and fm != "n") or (int(inp) < 1 and int(inp) > 9) or (len(state) > 10):
        valid = False
    
    return valid

def main():
    if validate(fm, inp, state):
        execute(fm, inp, state)
    else:
        print("Invalid input")

# run the application.
if __name__ == "__main__":
    # Setting debug to True enables debug output. This line should be
    # removed before deploying a production application.
    application.debug = True
    application.run()