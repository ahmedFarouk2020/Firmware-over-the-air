import global_data as gd
import os

class FileHandling():
    def __init__(self) -> None:
        self.filename = gd.filename
        self.lines_countA = 0
        self.lines_countB = 0
        self.update_exist = False
        print("inside init")
        self.num_of_lines()
        print("end of init")
    

    
    def num_of_lines(self):
        # empty the list
        gd.file_list[0].clear()
        gd.file_list[1].clear()
        
        try: # if there is a file -> read it
            self.file = open(self.filename,'rt')
            while  True :
                line = self.file.readline()
                if line[0] != '*':
                    # store in list
                    gd.file_list[0].append(line)
                    self.lines_countA = self.lines_countA + 1

                else:
                    break

            while True:
                line = self.file.readline()
                if line != '':
                    # store in list
                    gd.file_list[1].append(line)
                    self.lines_countB = self.lines_countB + 1

                else:
                    break
            self.update_exist = True
            
        except: # if there is no files -> update_exist = False
            self.update_exist = False
        # store number of line in bankA inside lines count 
        gd.lines_count = self.lines_countA
        print(f'lines count = {gd.lines_count}')
        print(f'lines count = {self.lines_countB}')
        


    def Is_Update_Exist(self):
        return self.update_exist



    def get_lines(self, count):
        lines = []
        for index in range(count):
            lines.append(self.file.readline())

        return lines

    def close_file(self):
        self.file.close()
        os.remove(self.filename)
