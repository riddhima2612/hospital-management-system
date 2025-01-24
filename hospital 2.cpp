#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

class Person {
protected:
    std::string name;
    int age;
    std::string gender;

public:
    Person(std::string n, int a, std::string g) : name(n), age(a), gender(g) {}
    virtual void display() const = 0;
};

class Patient : public Person {
private:
    int patientId;
    std::string medicalHistory;
    std::vector<std::string> medications;
    std::vector<std::string> labResults;

public:
    Patient(std::string n, int a, std::string g, int id)
        : Person(n, a, g), patientId(id) {}

    void addMedicalHistory(const std::string& history) {
        medicalHistory = history;
    }

    void addMedication(const std::string& med) {
        medications.push_back(med);
    }

    void addLabResult(const std::string& result) {
        labResults.push_back(result);
    }

    void display() const override {
        std::cout << "Patient ID: " << patientId << ", Name: " << name
                  << ", Age: " << age << ", Gender: " << gender << std::endl;
        std::cout << "Medical History: " << medicalHistory << std::endl;
        std::cout << "Medications: ";
        for (const auto& med : medications) {
            std::cout << med << ", ";
        }
        std::cout << "\nLab Results: ";
        for (const auto& result : labResults) {
            std::cout << result << ", ";
        }
        std::cout << std::endl;
    }

    void saveToFile() const {
        std::ofstream file("patients.txt", std::ios::app);
        file << patientId << "," << name << "," << age << "," << gender << ","
             << medicalHistory << std::endl;
        file.close();
    }
};

class Doctor : public Person {
private:
    int doctorId;
    std::string specialization;

public:
    Doctor(std::string n, int a, std::string g, int id, std::string spec)
        : Person(n, a, g), doctorId(id), specialization(spec) {}

    void display() const override {
        std::cout << "Doctor ID: " << doctorId << ", Name: " << name
                  << ", Age: " << age << ", Gender: " << gender
                  << ", Specialization: " << specialization << std::endl;
    }

    void saveToFile() const {
        std::ofstream file("doctors.txt", std::ios::app);
        file << doctorId << "," << name << "," << age << "," << gender << ","
             << specialization << std::endl;
        file.close();
    }
};

class Appointment {
private:
    int appointmentId;
    int patientId;
    int doctorId;
    std::string date;
    std::string time;

public:
    Appointment(int appId, int patId, int docId, std::string d, std::string t)
        : appointmentId(appId), patientId(patId), doctorId(docId), date(d), time(t) {}

    void display() const {
        std::cout << "Appointment ID: " << appointmentId
                  << ", Patient ID: " << patientId
                  << ", Doctor ID: " << doctorId
                  << ", Date: " << date
                  << ", Time: " << time << std::endl;
    }

    void saveToFile() const {
        std::ofstream file("appointments.txt", std::ios::app);
        file << appointmentId << "," << patientId << "," << doctorId << ","
             << date << "," << time << std::endl;
        file.close();
    }
};

class HospitalManagementSystem {
private:
    std::vector<Patient> patients;
    std::vector<Doctor> doctors;
    std::vector<Appointment> appointments;

public:
    void addPatient(const Patient& patient) {
        patients.push_back(patient);
        patient.saveToFile();
    }

    void addDoctor(const Doctor& doctor) {
        doctors.push_back(doctor);
        doctor.saveToFile();
    }

    void scheduleAppointment(const Appointment& appointment) {
        appointments.push_back(appointment);
        appointment.saveToFile();
    }

    void displayAllPatients() const {
        for (const auto& patient : patients) {
            patient.display();
            std::cout << "------------------------" << std::endl;
        }
    }

    void displayAllDoctors() const {
        for (const auto& doctor : doctors) {
            doctor.display();
            std::cout << "------------------------" << std::endl;
        }
    }

    void displayAllAppointments() const {
        for (const auto& appointment : appointments) {
            appointment.display();
            std::cout << "------------------------" << std::endl;
        }
    }

    void loadDataFromFiles() {
        // Load patients
        std::ifstream patientFile("patients.txt");
        if (patientFile.is_open()) {
            std::string line;
            while (getline(patientFile, line)) {
                // Parse the line and create Patient objects
                // This is a simplified version and doesn't include all fields
                int id, age;
                std::string name, gender, history;
                sscanf(line.c_str(), "%d,%[^,],%d,%[^,],%[^,]", &id, name.data(), &age, gender.data(), history.data());
                Patient p(name, age, gender, id);
                p.addMedicalHistory(history);
                patients.push_back(p);
            }
            patientFile.close();
        }

        // Load doctors (similar to loading patients)
        // Load appointments (similar to loading patients)
    }
};

int main() {
    HospitalManagementSystem hms;
    hms.loadDataFromFiles();

    int choice;
    do {
        std::cout << "\nHospital Management System\n";
        std::cout << "1. Add Patient\n";
        std::cout << "2. Add Doctor\n";
        std::cout << "3. Schedule Appointment\n";
        std::cout << "4. Display All Patients\n";
        std::cout << "5. Display All Doctors\n";
        std::cout << "6. Display All Appointments\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, gender, history;
                int age, id;
                std::cout << "Enter patient details (ID, Name, Age, Gender): ";
                std::cin >> id >> name >> age >> gender;
                std::cout << "Enter medical history: ";
                std::cin.ignore();
                std::getline(std::cin, history);
                Patient p(name, age, gender, id);
                p.addMedicalHistory(history);
                hms.addPatient(p);
                break;
            }
            case 2: {
                std::string name, gender, specialization;
                int age, id;
                std::cout << "Enter doctor details (ID, Name, Age, Gender, Specialization): ";
                std::cin >> id >> name >> age >> gender >> specialization;
                Doctor d(name, age, gender, id, specialization);
                hms.addDoctor(d);
                break;
            }
            case 3: {
                int appId, patId, docId;
                std::string date, time;
                std::cout << "Enter appointment details (AppID, PatientID, DoctorID, Date, Time): ";
                std::cin >> appId >> patId >> docId >> date >> time;
                Appointment a(appId, patId, docId, date, time);
                hms.scheduleAppointment(a);
                break;
            }
            case 4:
                hms.displayAllPatients();
                break;
            case 5:
                hms.displayAllDoctors();
                break;
            case 6:
                hms.displayAllAppointments();
                break;
            case 0:
                std::cout << "Exiting program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}