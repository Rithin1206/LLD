// Problem statement:
// Design Unix File Search API to search file with different arguments as "extension", "name", "size" ...
// The design should be maintainable to add new contraints.


// implemnet linux find command as an api ,the api will support finding files that has given size requirements and a file with a certain format like

// find all file >5mb
// find all xml


class Component{
    public:
    string name;
    vector<Component*> childrenComponents;
    bool isFile;
};

class Directory: public Component{
    public:
    Directory(string _name){
        this->name= _name;
        isFile = false;
    }
    
};

class File: public Component{
    public:
    string extension;
    int size;
    
    File(string _name, string _ext, int _sz){
        this->name= _name;
        this->extension = _ext;
        this->size = _sz;
        isFile = true;
    }
    
};

class FilterStrategy{
    public:
    FilterStrategy* strat;
    bool performOr;
    virtual bool filter(File* f)= 0;
};

class NameFilter: public FilterStrategy{
    public:
    string name;
    NameFilter(string _name, FilterStrategy* _strat, bool _performOr){
        this->name = _name;
        this->strat = _strat;
        this->performOr = _performOr;
    }
    
    bool filter(File* f) override{
        bool res = (f->name == this->name);
        if(!strat)
            return res;
        if(performOr){
            return res or strat->filter(f);
        } else{
            return res and strat->filter(f);
        }
    }
};


class SizeFilter: public FilterStrategy{
    public:
    int size;
    SizeFilter(int _size, FilterStrategy* _strat, bool _performOr){
        this->size = _size;
        this->strat = _strat;
        this->performOr = _performOr;
    }
    
    bool filter(File* f) override{
        bool res = (f->size <= this->size);
        if(!strat)
            return res;
        if(performOr){
            return res or strat->filter(f);
        } else{
            return res and strat->filter(f);
        }
    }
};

class ExtensionFilter: public FilterStrategy{
    public:
    string extension;
    ExtensionFilter(string _ext, FilterStrategy* _strat, bool _performOr){
        this->extension = _ext;
        this->strat = _strat;
        this->performOr = _performOr;
    }
    
    bool filter(File* f) override{
        bool res = (f->extension == this->extension);
        if(!strat)
            return res;
        if(performOr){
            return res or strat->filter(f);
        } else{
            return res and strat->filter(f);
        }
    }
};

// file search API -> input as a Directory path and from that path I need to find all files and filter them
class FileSystem{
    public:
    Directory* root;
    FilterStrategy* fs;
    FileSystem(){
        this->root= new Directory("home");
    }
    
    void setFilterStrategy(FilterStrategy* _fs){
        this->fs =_fs;
    }
    
    // search
    vector<File*> getFiles(string path){ // "/src/dir"
        vector<string> folders;
        stringstream ss(path);
        string w;
        while(getline(ss, w, '/')){
            folders.push_back(w);
        }
        
        Component* curr = root;
        int n= folders.size();
        for(int i=0; i<n; i++){
            for(auto& c: curr->childrenComponents){
                if(!c->isFile and c->name == folders[i]){
                    curr = c;
                    break;
                }
            }
        }
        
        // at the directory head
        
        // list all the files
        vector<File*> ans;
        queue<Component*> q;
        q.push(curr);
        while(!q.empty()){
            Component* top = q.front();
            q.pop();
            for(auto &child: top->childrenComponents){
                if(child->isFile){
                    if(fs->filter((File*)child))
                        ans.push_back((File*)(child));
                }else{
                    q.push(child);
                }
            }
        }
        
        for(auto f:ans){
            cout<< f->name<<f->extension<<endl;
        }
        return ans;
    }
    
    
};




int main() {
    FileSystem* fs = new FileSystem();
    
    FilterStrategy* nameFilter = new NameFilter("file 1", NULL, true);
    FilterStrategy* nameExtFilter = new ExtensionFilter(".xml", nameFilter, true);
    FilterStrategy* nameExtSizeFilter = new SizeFilter( 5, nameExtFilter, true);
    fs->setFilterStrategy(nameExtSizeFilter);
    
    Component* root = fs->root;
    
    File* f1= new File("file 1", ".pdf", 15);
    File* f2= new File("file 2", ".xml", 10);
    File* f3= new File("file 3", ".csv", 15);
    File* f4= new File("file 4", ".txt", 5);
    File* f5= new File("file 5", ".cpp", 5);
    
    Directory* d1= new Directory("dir1");
    Directory* d2= new Directory("dir2");
    Directory* d3= new Directory("dir3");
    
    
    root->childrenComponents.push_back(f5); 
    root->childrenComponents.push_back(d1);
    d1->childrenComponents.push_back(f2);
    d1->childrenComponents.push_back(f4);
    d1->childrenComponents.push_back(d2);
    d2->childrenComponents.push_back(f3);
    d2->childrenComponents.push_back(d3);
    d3->childrenComponents.push_back(f1);
    
    
    fs->getFiles("");
    
    std::cout << "Hello World!\n";
}