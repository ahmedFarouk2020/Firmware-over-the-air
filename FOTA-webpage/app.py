from flask import Flask, render_template, redirect, request, jsonify

from werkzeug.utils import secure_filename
import global_data as gd
from File_handling import FileHandling


app = Flask(__name__)



@app.route("/")
def home():
    return render_template("index.html")

@app.route('/api/hasUpdate/')
def check_on_updates():
    # call readfile 0: no files   1: update exists
    hex_file = FileHandling()
    print("app1")
    update_status = hex_file.Is_Update_Exist()
    print("app2")
    # if there is an update -> 'y
    if update_status == True:
        return 'y'
    # if no updates -> 'n'
    else:
        return 'n'



@app.route('/api/CountNewFileLines/')
def count_lines():
    # All right  ->  number of file lines
    return str(gd.lines_count)
    # problems   ->  400 (bad request)
    return "count_lines"


@app.route('/api/receive/<string:bank_id>/<string:page_num>/<string:num_of_lines>/')
def receive_lines(bank_id, page_num, num_of_lines):
    lines_number = int(num_of_lines)
    lines_returned = []

    # page = 1  ->  start = 1   -> start = (page-1)*100 +1 
    # page = 2  ->  start = 101
    # page = 3  ->  start = 201

    # page = 1  ->  start = 1    -> start = (page-1)*80 +1  -> end = 80
    # page = 2  ->  start = 81   -> end = 160
    # page = 3  ->  start = 161  -> end = 240

    # return records from start line to end line
    start_line = (int(page_num)-1) * int(num_of_lines) + 1
    end_line = int(page_num) * int(num_of_lines)
    # load records in the returned list
    for line in range(start_line, end_line+1):
        if int(bank_id) == gd.BANK_A:

            # exceed number of lines ?
            try: 
                lines_returned.append(gd.file_list[0][line])
            except:
                break
        else: # Bank B
            # exceed number of lines ?
            try:
                lines_returned.append(gd.file_list[1][line])
            except:
                break

    # All right  ->  number of file lines
    # problems   ->  400 (bad request)
    
    return jsonify(lines_returned)



@app.route("/upload", methods = ['GET', 'POST'])
def read_file():
    if request.method == 'POST':

        f = request.files['file']
        gd.filename = f.filename
        print(gd.filename)
        f.save(secure_filename(f.filename))

        # file = open(f.filename, 'r')
        # # read line with added '\n' as delimiter
        # print(file.readline())
        # print(file.readline())
        # file.close()
        # # remove file after ending
        # os.remove(f.filename)
        # print(f.filename)
        print("uploaded")
        return redirect("/")

    print("not uploaded")
    return redirect("/")



@app.route('/home/error')
def prompt_error():
    return "<h1>ERROR</h1>"


if __name__ == '__main__' :
    app.run(debug=True)
