#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Patient Class
class Patient {
public:
    int patientID;
    string name;
    int age;
    string medicalHistory;

    Patient(int id, string n, int a, string mh) : patientID(id), name(n), age(a), medicalHistory(mh) {}

    void displayPatientInfo() {
        cout << "Patient ID: " << patientID << endl;
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Medical History: " << medicalHistory << endl;
    }
};

// Doctor Class
class Doctor {
public:
    int doctorID;
    string name;
    string specialty;

    Doctor(int id, string n, string s) : doctorID(id), name(n), specialty(s) {}

    void displayDoctorInfo() {
        cout << "Doctor ID: " << doctorID << endl;
        cout << "Name: " << name << endl;
        cout << "Specialty: " << specialty << endl;
    }
};

// Appointment Class
class Appointment {
public:
    Patient *patient;
    Doctor *doctor;
    string appointmentDate;

    Appointment(Patient *p, Doctor *d, string date) : patient(p), doctor(d), appointmentDate(date) {}

    void displayAppointmentInfo() {
        cout << "Appointment Date: " << appointmentDate << endl;
        cout << "Patient: " << patient->name << endl;
        cout << "Doctor: " << doctor->name << " (Specialty: " << doctor->specialty << ")" << endl;
    }
};

// Hospital Management System Class
class HospitalManagementSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

public:
    // Add a new patient
    void addPatient() {
        int id, age;
        string name, history;

        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Patient Name: ";
        cin >> name;
        cout << "Enter Patient Age: ";
        cin >> age;
        cout << "Enter Medical History: ";
        cin >> history;

        patients.push_back(Patient(id, name, age, history));
        cout << "Patient added successfully!" << endl;
    }

    // Add a new doctor
    void addDoctor() {
        int id;
        string name, specialty;

        cout << "Enter Doctor ID: ";
        cin >> id;
        cout << "Enter Doctor Name: ";
        cin >> name;
        cout << "Enter Doctor Specialty: ";
        cin >> specialty;

        doctors.push_back(Doctor(id, name, specialty));
        cout << "Doctor added successfully!" << endl;
    }

    // Schedule an appointment
    void addAppointment() {
        int patientID, doctorID;
        string date;

        cout << "Enter Patient ID: ";
        cin >> patientID;
        cout << "Enter Doctor ID: ";
        cin >> doctorID;
        cout << "Enter Appointment Date (DD/MM/YYYY): ";
        cin >> date;

        Patient *p = nullptr;
        Doctor *d = nullptr;

        for (auto &patient : patients) {
            if (patient.patientID == patientID) {
                p = &patient;
                break;
            }
        }

        for (auto &doctor : doctors) {
            if (doctor.doctorID == doctorID) {
                d = &doctor;
                break;
            }
        }

        if (p != nullptr && d != nullptr) {
            appointments.push_back(Appointment(p, d, date));
            cout << "Appointment scheduled successfully!" << endl;
        } else {
            cout << "Invalid patient or doctor ID!" << endl;
        }
    }

    // View all patients
    void viewPatients() {
        for (auto &patient : patients) {
            patient.displayPatientInfo();
            cout << "------------------" << endl;
        }
    }

    // View all doctors
    void viewDoctors() {
        for (auto &doctor : doctors) {
            doctor.displayDoctorInfo();
            cout << "------------------" << endl;
        }
    }

    // View all appointments
    void viewAppointments() {
        for (auto &appointment : appointments) {
            appointment.displayAppointmentInfo();
            cout << "------------------" << endl;
        }
    }
};

int main() {
    HospitalManagementSystem hms;
    int choice;

    while (true) {
        cout << "1. Add Patient\n2. Add Doctor\n3. Schedule Appointment\n4. View Patients\n5. View Doctors\n6. View Appointments\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hms.addPatient();
            break;
        case 2:
            hms.addDoctor();
            break;
        case 3:
            hms.addAppointment();
            break;
        case 4:
            hms.viewPatients();
            break;
        case 5:
            hms.viewDoctors();
            break;
        case 6:
            hms.viewAppointments();
            break;
        case 7:
            exit(0);
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
