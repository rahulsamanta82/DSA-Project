#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void clearBuffer() {
    cin.clear();
    while (cin.get() != '\n');
}

struct UserData {
    char role[20];
    char field1[50];
    char field2[50];
    char field3[50];
    char field4[50];
    char advice[100];
};

struct Job {
    char title[50];
    int expRequired;
    char skills[5][50];
    int skillCount;
    int salary;
};

Job availableJobs[3] = {
    {"Software Engineer", 2, {"C++", "DSA", "OOP", "Git"}, 4, 80000},
    {"Data Analyst", 1, {"Python", "SQL", "Statistics", "Excel"}, 4, 60000},
    {"Web Developer", 1, {"HTML", "CSS", "JavaScript", "React"}, 4, 70000}
};

class RecruitmentTerminal {
private:
    Job dynamicJobs[10];
    int dynamicCount;

public:
    RecruitmentTerminal() : dynamicCount(0) {}

    void printTable(UserData data, int mode) {
        std::cout << "\n\n" << ">>> GENERATING SYSTEM REPORT <<<" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        std::cout << "| Role         | Questions                    | Answers                     |" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;

        if (mode == 1) {
            std::cout << "| Recruiter    | Job Title                    | " << data.field1 << std::endl;
            std::cout << "|              | Required Experience          | " << data.field2 << std::endl;
            std::cout << "|              | Required Skills              | " << data.field3 << std::endl;
            std::cout << "|              | Salary Range                 | " << data.field4 << std::endl;
        } 
        else if (mode == 2) {
            std::cout << "| Student      | Skills                       | " << data.field1 << std::endl;
            std::cout << "|              | Experience Level             | " << data.field2 << std::endl;
        } 
        else if (mode == 3) {
            std::cout << "| Job Seeker   | Applying for Job             | " << data.field1 << std::endl;
            std::cout << "|              | Experience Level             | " << data.field2 << std::endl;
            std::cout << "|              | Suggested Skills             | " << data.field3 << std::endl;
        }
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
    }

    void saveJobToFile(Job job) {
        ofstream file("jobs.txt", ios::app);
        if (file.is_open()) {
            file << job.title << "," << job.expRequired << ",";
            for (int i = 0; i < job.skillCount; i++) {
                file << job.skills[i];
                if (i < job.skillCount - 1) file << ";";
            }
            file << "," << job.salary << endl;
            file.close();
        }
    }

    void loadJobsFromFile() {
        dynamicCount = 0;
        ifstream file("jobs.txt");
        if (!file.is_open()) {
            return;
        }
        string line;
        while (getline(file, line) && dynamicCount < 10) {
            if (line.empty()) continue;
            
            Job& job = dynamicJobs[dynamicCount++];
            size_t pos = 0;
            string token;
            int field = 0;
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                if (field == 0) strcpy(job.title, token.c_str());
                else if (field == 1) job.expRequired = stoi(token);
                else if (field == 2) {
                    size_t skillPos = 0;
                    string skillToken;
                    int skillIndex = 0;
                    while ((skillPos = token.find(';')) != string::npos) {
                        skillToken = token.substr(0, skillPos);
                        strcpy(job.skills[skillIndex++], skillToken.c_str());
                        token.erase(0, skillPos + 1);
                    }
                    strcpy(job.skills[skillIndex++], token.c_str());
                    job.skillCount = skillIndex;
                }
                field++;
            }
            job.salary = stoi(line);
        }
        file.close();
    }
    

    void applyForJob(const char* jobTitle) {
        char name[50], fatherName[50], cnic[20], cvPath[100];
        int expYears;

        std::cout << "\n\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                        JOB APPLICATION FORM                              ║" << std::endl;
        std::cout << "║                   Position: " << jobTitle;
        int spaces = 48 - strlen(jobTitle);
        for (int i = 0; i < spaces; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;

        std::cout << "\nFull Name: ";
        std::cin.getline(name, 50);
        std::cout << "Father's Name: ";
        std::cin.getline(fatherName, 50);
        std::cout << "CNIC: ";
        std::cin.getline(cnic, 20);
        std::cout << "Years of Experience: ";
        std::cin >> expYears;
        clearBuffer();
        std::cout << "CV Path/File Name: ";
        std::cin.getline(cvPath, 100);

        std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                    APPLICATION SUBMITTED SUCCESSFULLY!                    ║" << std::endl;
        std::cout << "║                                                                            ║" << std::endl;
        std::cout << "║  Applicant Name: " << name;
        for (int i = strlen(name); i < 58; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "║  Position Applied: " << jobTitle;
        for (int i = strlen(jobTitle); i < 55; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "║  CNIC: " << cnic;
        for (int i = strlen(cnic); i < 66; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "║  Father's Name: " << fatherName;
        for (int i = strlen(fatherName); i < 59; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "║                                                                            ║" << std::endl;
        std::cout << "║  The company will contact you if you are selected. Thank you!             ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
    }

    void showRecommendations(int score, const char* jobTitle) {
        std::cout << "\n\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                    PERSONALIZED RECOMMENDATIONS                           ║" << std::endl;
        std::cout << "║              For Position: " << jobTitle;
        int spaces = 42 - strlen(jobTitle);
        for (int i = 0; i < spaces; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;

        std::cout << "\n📊 YOUR SCORE: " << score << "%\n" << std::endl;

        if (score >= 80) {
            std::cout << "✓ EXCELLENT! You are well-prepared for this position!\n";
            std::cout << "Next Steps:\n";
            std::cout << "  1. Continue building projects\n";
            std::cout << "  2. Explore advanced topics in your specialization\n";
            std::cout << "  3. Prepare for technical interviews\n";
        } else if (score >= 60) {
            std::cout << "△ GOOD EFFORT! You have a solid foundation but need improvement.\n";
            std::cout << "Focus Areas:\n";
            std::cout << "  1. Advanced Data Structures & Algorithms\n";
            std::cout << "  2. System Design Principles\n";
            std::cout << "  3. More hands-on projects\n";
            std::cout << "Timeline: 2-3 months of focused learning\n";
        } else {
            std::cout << "✗ NEEDS IMPROVEMENT! Don't get discouraged, here's your roadmap:\n\n";
            std::cout << "PHASE 1 (Month 1-2): FUNDAMENTALS\n";
            std::cout << "  - Master Data Structures (Arrays, Linked Lists, Trees, Graphs)\n";
            std::cout << "  - Learn Big O Notation and Time Complexity\n";
            std::cout << "  - Solve 100+ DSA problems on LeetCode\n";
            std::cout << "  Resources: LeetCode, HackerRank, GeeksforGeeks\n\n";

            std::cout << "PHASE 2 (Month 2-3): CORE CONCEPTS\n";
            std::cout << "  - OOP Principles (Inheritance, Polymorphism, Encapsulation)\n";
            std::cout << "  - Design Patterns\n";
            std::cout << "  - Database Fundamentals (SQL/NoSQL)\n";
            std::cout << "  - Version Control (Git/GitHub)\n\n";

            std::cout << "PHASE 3 (Month 3-4): PRACTICAL SKILLS\n";
            std::cout << "  - Build 3-4 real projects\n";
            std::cout << "  - Contribute to open-source\n";
            std::cout << "  - Learn Web Frameworks (if applicable)\n";
            std::cout << "  - Cloud Basics (AWS/Azure/GCP)\n\n";

            std::cout << "PHASE 4 (Ongoing): SPECIALIZATION\n";
            std::cout << "  - Choose a specialization (AI/Cloud/Backend/DevOps)\n";
            std::cout << "  - Get certified\n";
            std::cout << "  - Practice mock interviews\n\n";

            std::cout << "MARKET DEMANDED SKILLS (2024-2025):\n";
            std::cout << "  1. Cloud Computing (AWS/Azure) - $110K-$180K\n";
            std::cout << "  2. AI/Machine Learning - $120K-$250K+\n";
            std::cout << "  3. DevOps & Kubernetes - $100K-$180K\n";
            std::cout << "  4. Data Engineering - $120K-$180K\n";
            std::cout << "  5. Cybersecurity - $100K-$170K\n\n";

            std::cout << "💡 PRO TIPS:\n";
            std::cout << "  • Code daily (at least 1-2 hours)\n";
            std::cout << "  • Join tech communities on Discord/Reddit\n";
            std::cout << "  • Read tech blogs and documentation\n";
            std::cout << "  • Participate in hackathons\n";
            std::cout << "  • Build portfolio on GitHub\n";
            std::cout << "  • Network with experienced developers\n\n";

            std::cout << "Comeback in 2-3 months and retake this assessment! You can do it! 💪\n";
        }

        std::cout << "\n════════════════════════════════════════════════════════════════════════════\n";
    }

    int assessSkills(const char* jobTitle) {
        int langScore = 0, logicScore = 0, criticalScore = 0;
        int totalLang = 0, totalLogic = 0, totalCritical = 0;
        char answer[10];

        std::cout << "\n\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                       SKILL ASSESSMENT TEST                              ║" << std::endl;
        std::cout << "║                     Position: " << jobTitle;
        int spaces = 41 - strlen(jobTitle);
        for (int i = 0; i < spaces; i++) std::cout << " ";
        std::cout << "║" << std::endl;
        std::cout << "║                  Total Questions: 6 | Passing Score: 80%                  ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;

        // Software Engineer Assessment
        if (strcmp(jobTitle, "Software Engineer") == 0) {
            std::cout << "\n[LANGUAGE SKILLS]\n";
            std::cout << "Question 1: What is C++?\n";
            std::cout << "  (a) Programming Language\n";
            std::cout << "  (b) Coffee\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                langScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLang++;

            std::cout << "\nQuestion 2: What is the difference between struct and class in C++?\n";
            std::cout << "  (a) Struct is public by default, class is private\n";
            std::cout << "  (b) No difference\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                langScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLang++;

            std::cout << "\n[LOGICAL THINKING]\n";
            std::cout << "Question 3: What is the time complexity of binary search?\n";
            std::cout << "  (a) O(log n)\n";
            std::cout << "  (b) O(n)\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                logicScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLogic++;

            std::cout << "\nQuestion 4: What does DSA stand for?\n";
            std::cout << "  (a) Data Structures and Algorithms\n";
            std::cout << "  (b) Digital Storage Access\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                logicScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLogic++;

            std::cout << "\n[CRITICAL THINKING]\n";
            std::cout << "Question 5: Why use Object-Oriented Programming (OOP)?\n";
            std::cout << "  (a) Code reusability and maintainability\n";
            std::cout << "  (b) Faster typing\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                criticalScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalCritical++;

            std::cout << "\nQuestion 6: What is Git primarily used for?\n";
            std::cout << "  (a) Version Control\n";
            std::cout << "  (b) Graphics editing\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                criticalScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalCritical++;

        } 
        // Data Analyst Assessment
        else if (strcmp(jobTitle, "Data Analyst") == 0) {
            std::cout << "\n[LANGUAGE SKILLS]\n";
            std::cout << "Question 1: What is Python primarily used for in data analysis?\n";
            std::cout << "  (a) Data manipulation and analysis\n";
            std::cout << "  (b) Making coffee\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                langScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLang++;

            std::cout << "\nQuestion 2: What is Pandas in Python?\n";
            std::cout << "  (a) A library for data manipulation\n";
            std::cout << "  (b) A type of bear\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                langScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLang++;

            std::cout << "\n[LOGICAL THINKING]\n";
            std::cout << "Question 3: What does SQL stand for?\n";
            std::cout << "  (a) Structured Query Language\n";
            std::cout << "  (b) Super Quick Logic\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                logicScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLogic++;

            std::cout << "\nQuestion 4: What is a primary key in a database?\n";
            std::cout << "  (a) A unique identifier for each record\n";
            std::cout << "  (b) The main password\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                logicScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLogic++;

            std::cout << "\n[CRITICAL THINKING]\n";
            std::cout << "Question 5: Why is data visualization important?\n";
            std::cout << "  (a) To communicate insights effectively\n";
            std::cout << "  (b) To make numbers look pretty\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                criticalScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalCritical++;

            std::cout << "\nQuestion 6: What is the purpose of statistical analysis?\n";
            std::cout << "  (a) To derive meaningful insights from data\n";
            std::cout << "  (b) To make numbers bigger\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                criticalScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalCritical++;

        } 
        // Web Developer Assessment
        else if (strcmp(jobTitle, "Web Developer") == 0) {
            std::cout << "\n[LANGUAGE SKILLS]\n";
            std::cout << "Question 1: What is HTML primarily used for?\n";
            std::cout << "  (a) Structure and markup of web pages\n";
            std::cout << "  (b) Making websites run faster\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                langScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLang++;

            std::cout << "\nQuestion 2: What is CSS used for?\n";
            std::cout << "  (a) Styling web pages\n";
            std::cout << "  (b) Creating databases\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                langScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLang++;

            std::cout << "\n[LOGICAL THINKING]\n";
            std::cout << "Question 3: What does CSS stand for?\n";
            std::cout << "  (a) Cascading Style Sheets\n";
            std::cout << "  (b) Computer System Security\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                logicScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLogic++;

            std::cout << "\nQuestion 4: What is JavaScript used for in web development?\n";
            std::cout << "  (a) Adding interactivity to web pages\n";
            std::cout << "  (b) Creating server security\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                logicScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalLogic++;

            std::cout << "\n[CRITICAL THINKING]\n";
            std::cout << "Question 5: Why is responsive design important?\n";
            std::cout << "  (a) To ensure websites work on all devices\n";
            std::cout << "  (b) To make loading faster\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                criticalScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalCritical++;

            std::cout << "\nQuestion 6: What is the Document Object Model (DOM)?\n";
            std::cout << "  (a) The structure of HTML elements in a page\n";
            std::cout << "  (b) A data storage system\n";
            std::cout << "Your Answer: ";
            std::cin.getline(answer, 10);
            if (answer[0] == 'a' || answer[0] == 'A') {
                criticalScore++;
                std::cout << "✓ Correct!\n";
            } else {
                std::cout << "✗ Incorrect! Correct answer: (a)\n";
            }
            totalCritical++;

        } else {
            std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
            std::cout << "║              Assessment not available for this position yet.            ║" << std::endl;
            std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
            return -1;
        }

        // Calculate percentages - FIX: Handle division by zero
        int langPercent = (totalLang > 0) ? (langScore * 100 / totalLang) : 0;
        int logicPercent = (totalLogic > 0) ? (logicScore * 100 / totalLogic) : 0;
        int criticalPercent = (totalCritical > 0) ? (criticalScore * 100 / totalCritical) : 0;
        int totalPercent = (langPercent + logicPercent + criticalPercent) / 3;

        std::cout << "\n\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                         ASSESSMENT RESULTS                               ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
        std::cout << "\n📈 Detailed Breakdown:\n";
        std::cout << "  Language Skills:      " << langPercent << "% (" << langScore << "/" << totalLang << ")\n";
        std::cout << "  Logical Thinking:     " << logicPercent << "% (" << logicScore << "/" << totalLogic << ")\n";
        std::cout << "  Critical Thinking:    " << criticalPercent << "% (" << criticalScore << "/" << totalCritical << ")\n";
        std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║                         OVERALL SCORE: " << totalPercent << "%";
        
        // FIX: Proper spacing calculation
        int scoreSpaces = 38 - (totalPercent >= 100 ? 3 : (totalPercent >= 10 ? 2 : 1));
        for (int i = 0; i < scoreSpaces; i++) std::cout << " ";
        std::cout << "║" << std::endl;

        if (totalPercent >= 80) {
            std::cout << "║                         STATUS: ✓ PASSED                                   ║" << std::endl;
        } else {
            std::cout << "║                         STATUS: ✗ NOT PASSED                              ║" << std::endl;
        }
        std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;

        std::cout << "\n[Score Visualization]\n";
        // FIX: Ensure no negative values in string constructor
        int langViz = (langPercent > 0) ? langPercent / 10 : 0;
        int logicViz = (logicPercent > 0) ? logicPercent / 10 : 0;
        int criticalViz = (criticalPercent > 0) ? criticalPercent / 10 : 0;
        
        std::cout << "Language:  " << std::string(langViz, '#') << std::string(10 - langViz, ' ') << " " << langPercent << "%\n";
        std::cout << "Logical:   " << std::string(logicViz, '#') << std::string(10 - logicViz, ' ') << " " << logicPercent << "%\n";
        std::cout << "Critical:  " << std::string(criticalViz, '#') << std::string(10 - criticalViz, ' ') << " " << criticalPercent << "%\n";

        return totalPercent;
    }

    void studentMode() {
        UserData sessionData = {};
        std::cout << "\n[STUDENT MODE]" << std::endl;
        std::cout << "What skills do you have? (e.g., C++, Python, Java): ";
        std::cin.getline(sessionData.field1, 50);
        std::cout << "How much experience do you have in your field? (in years): ";
        std::cin.getline(sessionData.field2, 50);
        printTable(sessionData, 2);

        int userExp = stoi(string(sessionData.field2));

        loadJobsFromFile();
        std::cout << "\n\n>>> JOBS MATCHING YOUR PROFILE <<<" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        std::cout << "| Job Title          | Exp Req | Skills                          | Salary |" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        
        int jobNum = 1;
        bool found = false;
        std::vector<std::string> displayedJobs;

        for (int i = 0; i < 3; i++) {
            if (availableJobs[i].expRequired <= userExp) {
                std::cout << jobNum << ". ";
                std::cout << "| " << availableJobs[i].title;
                for (int j = strlen(availableJobs[i].title); j < 19; j++) std::cout << " ";
                std::cout << "| " << availableJobs[i].expRequired << " years ";
                std::cout << "| ";
                for (int k = 0; k < availableJobs[i].skillCount; k++) {
                    std::cout << availableJobs[i].skills[k];
                    if (k < availableJobs[i].skillCount - 1) std::cout << ", ";
                }
                std::cout << " | $" << availableJobs[i].salary << " |" << std::endl;
                displayedJobs.push_back(availableJobs[i].title);
                found = true;
                jobNum++;
            }
        }

        for (int i = 0; i < dynamicCount; i++) {
            if (dynamicJobs[i].expRequired <= userExp) {
                std::cout << jobNum << ". ";
                std::cout << "| " << dynamicJobs[i].title;
                for (int j = strlen(dynamicJobs[i].title); j < 19; j++) std::cout << " ";
                std::cout << "| " << dynamicJobs[i].expRequired << " years ";
                std::cout << "| ";
                for (int k = 0; k < dynamicJobs[i].skillCount; k++) {
                    std::cout << dynamicJobs[i].skills[k];
                    if (k < dynamicJobs[i].skillCount - 1) std::cout << ", ";
                }
                std::cout << " | $" << dynamicJobs[i].salary << " |" << std::endl;
                displayedJobs.push_back(dynamicJobs[i].title);
                found = true;
                jobNum++;
            }
        }

        if (!found) {
            std::cout << "╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
            std::cout << "║                   OOPS! NO MATCHING JOBS FOR YOU YET!                    ║" << std::endl;
            std::cout << "║                                                                            ║" << std::endl;
            std::cout << "║  Your current profile doesn't match available jobs.                       ║" << std::endl;
            std::cout << "║  Gain more experience and skills to unlock opportunities!               ║" << std::endl;
            std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
            return;
        }

        std::cout << "-----------------------------------------------------------------------------" << std::endl;

        // Job Recommendations and Guidelines
        std::cout << "\n\n>>> JOB RECOMMENDATIONS AND GUIDELINES <<<" << std::endl;
        for (size_t i = 0; i < displayedJobs.size(); i++) {
            std::cout << "\n" << (i+1) << ". " << displayedJobs[i] << ":\n";
            if (displayedJobs[i] == "Software Engineer") {
                std::cout << "   - Focus on mastering Data Structures and Algorithms (DSA).\n";
                std::cout << "   - Learn Object-Oriented Programming (OOP) principles.\n";
                std::cout << "   - Practice version control with Git and GitHub.\n";
                std::cout << "   - Build projects in C++ and contribute to open-source.\n";
                std::cout << "   - Prepare for coding interviews on platforms like LeetCode.\n";
            } else if (displayedJobs[i] == "Data Analyst") {
                std::cout << "   - Master Python and libraries like Pandas and NumPy.\n";
                std::cout << "   - Learn SQL for database querying.\n";
                std::cout << "   - Understand statistics and data visualization tools like Excel or Tableau.\n";
                std::cout << "   - Work on real datasets to gain practical experience.\n";
                std::cout << "   - Build a portfolio of data analysis projects.\n";
            } else if (displayedJobs[i] == "Web Developer") {
                std::cout << "   - Learn HTML, CSS, and JavaScript fundamentals.\n";
                std::cout << "   - Familiarize with frameworks like React or Angular.\n";
                std::cout << "   - Understand responsive design and CSS preprocessors.\n";
                std::cout << "   - Practice building full-stack web applications.\n";
                std::cout << "   - Deploy projects on platforms like GitHub Pages or Heroku.\n";
            } else {
                std::cout << "   - Research the specific skills required for this role.\n";
                std::cout << "   - Gain relevant experience through projects or internships.\n";
                std::cout << "   - Network with professionals in the field.\n";
                std::cout << "   - Tailor your resume to highlight matching skills.\n";
            }
        }

        std::cout << "\nWhich job are you interested in? Enter the number: ";
        int choice;
        std::cin >> choice;
        clearBuffer();

        const char* selectedJob = nullptr;
        if (choice > 0 && choice <= (int)displayedJobs.size()) {
            selectedJob = displayedJobs[choice - 1].c_str();
        } else {
            std::cout << "Invalid choice!\n";
            return;
        }

        std::cout << "\n✓ You selected: " << selectedJob << std::endl;
        
        std::cout << "\nDo you want to take the skill assessment for this position? (y/n): ";
        char takeTest[10];
        std::cin.getline(takeTest, 10);
        
        if (takeTest[0] == 'y' || takeTest[0] == 'Y') {
            std::cout << "Now let's test your skills for this position!\n";
            
            int score = assessSkills(selectedJob);

            if (score == -1) {
                std::cout << "\nAssessment not available for this position. You are applicable for this position.\n";
                std::cout << "\nProceeding to Application Form...\n";
                applyForJob(selectedJob);
            } else if (score >= 80) {
                std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                  🎉 CONGRATULATIONS! YOU PASSED! 🎉                       ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
                std::cout << "\nProceeding to Application Form...\n";
                applyForJob(selectedJob);
            } else {
                std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                    ⚠️  YOU DIDN'T PASS THIS TIME ⚠️                        ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
                std::cout << "\nDo you want personalized recommendations? (y/n): ";
                char wantTips[10];
                std::cin.getline(wantTips, 10);
                if (wantTips[0] == 'y' || wantTips[0] == 'Y') {
                    showRecommendations(score, selectedJob);
                }
            }
        } else {
            std::cout << "\nProceeding to Application Form...\n";
            applyForJob(selectedJob);
        }
    }

    void jobSeekerMode() {
        UserData sessionData = {};
        std::cout << "\n[JOB SEEKER MODE]" << std::endl;
        std::cout << "Which job are you applying for? ";
        std::cin.getline(sessionData.field1, 50);
        std::cout << "How much experience do you have? (in years): ";
        std::cin.getline(sessionData.field2, 50);
        
        printTable(sessionData, 3);

        std::cout << "\n✓ You selected: " << sessionData.field1 << std::endl;
        
        std::cout << "\nDo you want to take the skill assessment for this position? (y/n): ";
        char takeTest[10];
        std::cin.getline(takeTest, 10);
        
        if (takeTest[0] == 'y' || takeTest[0] == 'Y') {
            std::cout << "Now let's test your skills for this position!\n";
            
            int score = assessSkills(sessionData.field1);

            if (score == -1) {
                std::cout << "\nAssessment not available for this position. You are applicable for this position.\n";
                std::cout << "\nProceeding to Application Form...\n";
                applyForJob(sessionData.field1);
            } else if (score >= 80) {
                std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                  🎉 CONGRATULATIONS! YOU PASSED! 🎉                       ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
                std::cout << "\nProceeding to Application Form...\n";
                applyForJob(sessionData.field1);
            } else {
                std::cout << "\n╔════════════════════════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║                    ⚠️  YOU DIDN'T PASS THIS TIME ⚠️                        ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════════════════════════╝" << std::endl;
                std::cout << "\nDo you want personalized recommendations? (y/n): ";
                char wantTips[10];
                std::cin.getline(wantTips, 10);
                if (wantTips[0] == 'y' || wantTips[0] == 'Y') {
                    showRecommendations(score, sessionData.field1);
                }
            }
        } else {
            std::cout << "\nProceeding to Application Form...\n";
            applyForJob(sessionData.field1);
        }
    }

    void displayAllJobs() {
        loadJobsFromFile();
        std::cout << "\n\n>>> ALL AVAILABLE JOBS <<<" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        std::cout << "| Job Title          | Exp Req | Skills                          | Salary |" << std::endl;
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
        
        for (int i = 0; i < 3; i++) {
            std::cout << "| " << availableJobs[i].title;
            for (int j = strlen(availableJobs[i].title); j < 19; j++) std::cout << " ";
            std::cout << "| " << availableJobs[i].expRequired << " years ";
            std::cout << "| ";
            for (int k = 0; k < availableJobs[i].skillCount; k++) {
                std::cout << availableJobs[i].skills[k];
                if (k < availableJobs[i].skillCount - 1) std::cout << ", ";
            }
            std::cout << " | $" << availableJobs[i].salary << " |" << std::endl;
        }
        
        for (int i = 0; i < dynamicCount; i++) {
            std::cout << "| " << dynamicJobs[i].title;
            for (int j = strlen(dynamicJobs[i].title); j < 19; j++) std::cout << " ";
            std::cout << "| " << dynamicJobs[i].expRequired << " years ";
            std::cout << "| ";
            for (int k = 0; k < dynamicJobs[i].skillCount; k++) {
                std::cout << dynamicJobs[i].skills[k];
                if (k < dynamicJobs[i].skillCount - 1) std::cout << ", ";
            }
            std::cout << " | $" << dynamicJobs[i].salary << " |" << std::endl;
        }
        
        std::cout << "-----------------------------------------------------------------------------" << std::endl;
    }

    void gapAnalyzer() {
        int score;
        std::cout << "\n\n>>> GAP ANALYZER <<<" << std::endl;
        std::cout << "=====================================================================" << std::endl;
        std::cout << "Enter your assessment score percentage (0-100): ";
        std::cin >> score;
        clearBuffer();

        std::cout << "\n>>> MARKET TRENDS & DEMANDED SKILLS (2024-2025) <<<\n";
        std::cout << "=====================================================================" << std::endl;
        std::cout << "\n1. ARTIFICIAL INTELLIGENCE & MACHINE LEARNING\n";
        std::cout << "   - Most demanded skill set\n";
        std::cout << "   - Skills: Python, TensorFlow, PyTorch, NLP, Computer Vision\n";
        std::cout << "   - Salary: $150K - $250K+\n";

        std::cout << "\n2. CLOUD COMPUTING & DEVOPS\n";
        std::cout << "   - Rapidly growing demand\n";
        std::cout << "   - Skills: AWS, Azure, Docker, Kubernetes, CI/CD\n";
        std::cout << "   - Salary: $110K - $200K\n";

        std::cout << "\n3. DATA ENGINEERING\n";
        std::cout << "   - High market demand\n";
        std::cout << "   - Skills: SQL, Spark, Hadoop, Python, ETL\n";
        std::cout << "   - Salary: $120K - $200K\n";

        std::cout << "\n4. CYBERSECURITY\n";
        std::cout << "   - Critical need\n";
        std::cout << "   - Skills: Network Security, Encryption, Penetration Testing\n";
        std::cout << "   - Salary: $100K - $180K\n";

        std::cout << "\n5. BLOCKCHAIN & WEB3\n";
        std::cout << "   - Emerging technology\n";
        std::cout << "   - Skills: Solidity, Smart Contracts, Cryptography\n";
        std::cout << "   - Salary: $90K - $180K\n";

        std::cout << "\n════════════════════════════════════════════════════════════════════════════\n";
    }

    void start() {
        int choice;
        UserData sessionData = {};

        std::cout << "====================================================" << std::endl;
        std::cout << "       JOB APPLICATION AND SKILL GAP ANALYZER       " << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << "Please specify your role:\n1. Recruiter\n2. Student\n3. Job Seeker\n4. View All Jobs\n5. Market Trends & Gap Analyzer\n6. Exit\n\nEnter number: ";
        std::cin >> choice;
        clearBuffer();

        if (choice == 1) {
            bool addMore = true;
            while (addMore) {
                std::cout << "\n[RECRUITER MODE]" << std::endl;
                std::cout << "What is the job title you are hiring for? ";
                std::cin.getline(sessionData.field1, 50);
                std::cout << "What is the required experience for this position? ";
                std::cin.getline(sessionData.field2, 50);
                std::cout << "What skills should the applicant possess? ";
                std::cin.getline(sessionData.field3, 50);
                std::cout << "What is the salary range for this position? ";
                std::cin.getline(sessionData.field4, 50);
                printTable(sessionData, 1);

                Job newJob;
                strcpy(newJob.title, sessionData.field1);
                newJob.expRequired = stoi(string(sessionData.field2));
                newJob.skillCount = 1;
                strcpy(newJob.skills[0], sessionData.field3);
                newJob.salary = stoi(string(sessionData.field4));
                saveJobToFile(newJob);

                std::cout << "\nJob posted successfully!\n";
                std::cout << "Would you like to add another job hiring? (yes/no): ";
                char addChoice[10];
                std::cin.getline(addChoice, 10);
                if (addChoice[0] != 'y' && addChoice[0] != 'Y') {
                    addMore = false;
                }
            }
        } 
        else if (choice == 2) {
            studentMode();
        } 
        else if (choice == 3) {
            jobSeekerMode();
        } 
        else if (choice == 4) {
            displayAllJobs();
        }
        else if (choice == 5) {
            gapAnalyzer();
        }
        else if (choice == 6) {
            std::cout << "Exiting system...\n";
            exit(0);
        }
        else {
            std::cout << "Invalid selection. Try again.\n";
        }
    }
};

int main() {
    RecruitmentTerminal terminal;
    while (true) {
        terminal.start();
    }
    return 0;
}