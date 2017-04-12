from flask import Flask
from flask import request
import json
app = Flask(__name__)

@app.route("/send_code", methods=["GET"])
def getCode():
    print "------------------------------"
    print "code:"
    print request.args.get("code")
    print "ship:"
    print request.args.get("ship")
    print "------------------------------"
    return  ""

if __name__ == "__main__":
    app.run(host="0.0.0.0")
