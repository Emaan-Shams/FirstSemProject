#include<stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char doctor[25];
    char reason[50];
    char area[25];
    char hospital[50];
    char date[12];
} Appointment;

void getDoctor(char doctor[], int area, int hospital);
int isDateAvailable(const char *filename, const char *date);

int main() {
    int i,hospital, area,time;
    char doctor[25];
    char reason[50];
    char timing[15];
    char areaName[25], hospitalName[50], date[12],TimeSlots[9];
    FILE *file;


    while(1){
        printf("\n====================================\n");
		printf("    Hospital Appointment System");
		 printf("\n====================================\n");
		printf("------Select Area------");
		printf("\n1.CLifton\n2.DHA\n3.Gulshan-e-Iqbal\n4.Saddar\n5.North Nazimabad\n");
		printf("Enter your choice:");
		scanf("%d", &area);
		
		printf("\n------Select Hospital------");
        switch(area){
			case 1:
				printf("\n1.Agha Khan Health Centre\n2.Ziauddin Hospital\n3.South City Hospital");
				printf("\nEnter your choice:");
				scanf("%d",&hospital);
				break;
			case 2:
				printf("\n1.PAF Hospital\n2.MediCare Cardiac & General Hospital\n3.Australian Concept Fertility Centre");
				printf("\nEnter your choice:");
				scanf("%d",&hospital);
				break;
			case 3:
				printf("\n1.Liaquat National Hospital\n2.Mamji Hospital\n3.Tabba Heart Institute");
				printf("\nEnter your choice:");
				scanf("%d",&hospital);
				break;
			case 4:
				printf("\n1.Jinnah Postgraduate Medical Centre(JPMC)\n2.Civil Hospital\n3.National Institute of Child Health");
				printf("\nEnter your choice:");
				scanf("%d",&hospital);
				break;
			case 5:
				printf("\n1.Ziauddin Hospital\n2.Saifee Hospital\n3.Abbasi Shaheed Hospital");
				printf("\nEnter your choice:");
				scanf("%d",&hospital);
				break;
            default:
                printf("Invalid area selection.\n"); continue;
        }

        getDoctor(doctor, area, hospital);

        printf("Please share the reason of your visit: ");
        getchar(); 
        fgets(reason, sizeof(reason), stdin);
        reason[strcspn(reason, "\n")] = '\0';

        printf("Enter appointment date (YYYY-MM-DD): ");
        fgets(date, sizeof(date), stdin);
        date[strcspn(date, "\n")] = '\0';
    
        // Check if date is available
        if(!isDateAvailable("appointments.txt", date)){
            printf("Sorry, an appointment already exists for this date. Please select another date.\n");
            continue; // Return to menu
        }
    	
    	SelectTime();
    	
    	//Update Doctor Schedule when new appointment is made
        switch(time){
        	case 1: strcpy(timing,"8:00 AM");
        	case 2: strcpy(timing,"9:00 AM");
        	case 3: strcpy(timing,"10:00 AM");
        	case 4: strcpy(timing,"11:00 AM");
        	case 5: strcpy(timing,"12:00 PM");
        	case 6: strcpy(timing,"1:00 PM");
        	case 7: strcpy(timing,"2:00 PM");
        	case 8: strcpy(timing,"3:00 PM");
        	case 9: strcpy(timing,"4:00 PM");
		}

        // record area and hospital names
        switch(area) {
            case 1: strcpy(areaName, "Clifton"); break;
            case 2: strcpy(areaName, "DHA"); break;
            case 3: strcpy(areaName, "Gulshan-e-Iqbal"); break;
            case 4: strcpy(areaName, "Saddar"); break;
            case 5: strcpy(areaName, "North Nazimabad"); break;
        }
        switch(hospital) {
            case 1:
                if(area==1){
					strcpy(hospitalName,"Agha Khan Health Centre");
				}
                else if(area==2){
					strcpy(hospitalName,"PAF Hospital");
				}
                else if(area==3){
					strcpy(hospitalName,"Liaquat National Hospital");
				}
                else if(area==4) {
					strcpy(hospitalName,"JPMC");
				}
                else{
					strcpy(hospitalName,"Ziauddin Hospital");
				}
                break;
            case 2:
                if(area==1){
					strcpy(hospitalName,"Ziauddin Hospital");
				}
                else if(area==2){
					strcpy(hospitalName,"MediCare Cardiac & General Hospital");
				}
                else if(area==3) {
					strcpy(hospitalName,"Mamji Hospital");
				}
                else if(area==4){
					strcpy(hospitalName,"Civil Hospital");
				}
                else{
					strcpy(hospitalName,"Saifee Hospital");
				}
                break;
            case 3:
                if(area==1){
					strcpy(hospitalName,"South City Hospital");
				}
                else if(area==2){
					strcpy(hospitalName,"Australian Concept Fertility Centre");
				}
                else if(area==3){
					strcpy(hospitalName,"Tabba Heart Institute");
				}
                else if(area==4) {
					strcpy(hospitalName,"National Institute of Child Health");
				}
                else {
					strcpy(hospitalName,"Abbasi Shaheed Hospital");
				}
                break;
        }

        // Append appointment to file
        file = fopen("appointments.txt", "a");
        if(file == NULL){
            printf("Error opening file!\n");
            return 1;
        }
        fprintf(file, "%s|%s|%s|%s|%s\n", date, areaName, hospitalName, doctor, reason);
        
        fclose(file);

        printf("\n----------------------Appointment made successfully-------------------------\n");
        printf("Your Appointment has been made with %s\nDate: %s\nTime:%s\n Area: %s\nHospital: %s\nCause of Visit: %s\n",
               doctor, date,timing, areaName, hospitalName, reason);
        break; // Exit menu after successful appointment
    }

    return 0;
}

// Function to check if the date is available
int isDateAvailable(const char *filename, const char *date){
    FILE *file = fopen(filename, "r");
    if(!file) return 1; // File doesn't exist, so date is available

    char line[200], existingDate[12];
    while(fgets(line, sizeof(line), file)){
        scanf(line, "%[^|]", existingDate);
        if(strcmp(existingDate, date) == 0){
            fclose(file);
            return 0; // Date already exists
        }
    }
    fclose(file);
    return 1; // Date is available
}

// Recursive Function to select Time slot
void SelectTime(){
	int i,time;
	char TimeSlots[9];
	for(i = 0; i < 9; i++) {
    	TimeSlots[i] = 'A'; // All slots available initially
	}
	printf("Enter your preffered time slot:\n1.8:00 AM\n2.9:00 AM\n3.10:00 AM\n4.11:00 AM\n5.12:00 PM\n6.1:00 PM\n7.2:00 PM\n8.3:00 PM\n9.4:00 PM");
    scanf("%d", &time);
     if(TimeSlots[time-1]!='B'){
        TimeSlots[time-1]=='B';
	}
	else{
		printf("Sorry, this time slot is already booked\n");
		SelectTime();
	}
}

// Function to select doctor
void getDoctor(char doctor[], int area, int hospital){
    int doc;
    printf("\n------Select Your Doctor------\n");
    
    if(area==1){
        switch(hospital){
            case 1: 
				printf("1. Dr.Asma Majeed\n2. Dr.Talha Rehman\n3. Dr.Wajiha Nazir\n");
				break;
            case 2:
				printf("1. Dr.Mujeeb Farhan\n2. Dr.Sara Taufeeq\n3. Dr.Emaan Shams\n"); 
				break;
            case 3: 
				printf("1. Dr.Ali Mughal\n2. Dr.Marium Jamshed\n3. Dr.Zara Bilal\n"); 
				break;
        }
    } else if(area==2){
        switch(hospital){
            case 1: 
				printf("1. Dr.Safeer\n2. Dr.Saad Ali\n3. Dr.Amna Rehan\n"); 
				break;
            case 2: 
				printf("1. Dr.Mahrukh\n2. Dr.Roha Nadeem\n3. Dr.Shaffan Ahmed\n"); 
				break;
            case 3: 
				printf("1. Dr.Rabia Asghar\n2. Dr.Zaevia Haidar\n3. Dr.Ameera Ahsan\n"); 
				break;
        }
    } else if(area==3){
        switch(hospital){
            case 1: 
				printf("1. Dr.Noor\n2. Dr.Naveen\n3. Dr.Shariq Khan\n"); 
				break;
            case 2: 
				printf("1. Dr.Ayesha Kashif\n2. Dr.Maira\n3. Dr.Umar Rehman\n"); 
				break;
            case 3: 
				printf("1. Dr.Hamza Rizwan\n2. Dr.Anoosha Adnan\n3. Dr.Aleeya Zahra\n"); 
				break;
        }
    } 
	else if(area==4){
        switch(hospital){
            case 1: 
				printf("1. Dr.Rehum Arif\n2. Dr.Mujtaba\n3. Dr.Aayan Nasir\n"); 
				break;
            case 2: 
				printf("1. Dr.Khadija Bukhari\n2. Dr.Shanzay\n3. Dr.Ibrahim Shahzad\n"); 
				break;
            case 3: 
				printf("1. Dr.Abiya\n2. Dr.Amna Kaleem\n3. Dr.Muhammad Saif\n"); 
				break;
        }
    } 
	else if(area==5){
        switch(hospital){
            case 1: 
				printf("1. Dr.Leena\n2. Dr.Taha Junaidi\n3. Dr.Sohaib\n"); 
				break;
            case 2: 
				printf("1. Dr.Syeda Ramla\n2. Dr.Eshaal Fatima\n3. Dr.Abrar\n"); 
				break;
            case 3: 
				printf("1. Dr.Ebad\n2. Dr.Zubair\n3. Dr.Adeel Javed\n"); break;
        }
    }

    scanf("%d",&doc);

    // Assign doctor based on selection
    if(area==1){
        if(hospital==1){ strcpy(doctor, doc==1?"Dr.Asma Majeed":doc==2?"Dr.Talha Rehman":"Dr.Wajiha Nazir"); }
        else if(hospital==2){ strcpy(doctor, doc==1?"Dr.Mujeeb Farhan":doc==2?"Dr.Sara Taufeeq":"Dr.Emaan Shams"); }
        else{ strcpy(doctor, doc==1?"Dr.Ali Mughal":doc==2?"Dr.Marium Jamshed":"Dr.Zara Bilal"); }
    } else if(area==2){
        if(hospital==1){ strcpy(doctor, doc==1?"Dr.Safeer":doc==2?"Dr.Saad Ali":"Dr.Amna Rehan"); }
        else if(hospital==2){ strcpy(doctor, doc==1?"Dr.Mahrukh":doc==2?"Dr.Roha Nadeem":"Dr.Shaffan Ahmed"); }
        else{ strcpy(doctor, doc==1?"Dr.Rabia Asghar":doc==2?"Dr.Zaevia Haidar":"Dr.Ameera Ahsan"); }
    } else if(area==3){
        if(hospital==1){ strcpy(doctor, doc==1?"Dr.Noor":doc==2?"Dr.Naveen":"Dr.Shariq Khan"); }
        else if(hospital==2){ strcpy(doctor, doc==1?"Dr.Ayesha Kashif":doc==2?"Dr.Maira":"Dr.Umar Rehman"); }
        else{ strcpy(doctor, doc==1?"Dr.Hamza Rizwan":doc==2?"Dr.Anoosha Adnan":"Dr.Aleeya Zahra"); }
    } else if(area==4){
        if(hospital==1){ strcpy(doctor, doc==1?"Dr.Rehum Arif":doc==2?"Dr.Mujtaba":"Dr.Aayan Nasir"); }
        else if(hospital==2){ strcpy(doctor, doc==1?"Dr.Khadija Bukhari":doc==2?"Dr.Shanzay":"Dr.Ibrahim Shahzad"); }
        else{ strcpy(doctor, doc==1?"Dr.Abiya":doc==2?"Dr.Amna Kaleem":"Dr.Muhammad Saif"); }
    } else if(area==5){
        if(hospital==1){ strcpy(doctor, doc==1?"Dr.Leena":doc==2?"Dr.Taha Junaidi":"Dr.Sohaib"); }
        else if(hospital==2){ strcpy(doctor, doc==1?"Dr.Syeda Ramla":doc==2?"Dr.Eshaal Fatima":"Dr.Abrar"); }
        else{ strcpy(doctor, doc==1?"Dr.Ebad":doc==2?"Dr.Zubair":"Dr.Adeel Javed"); }
    }
}
