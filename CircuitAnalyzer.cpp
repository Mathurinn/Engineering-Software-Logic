#include <iostream>
#include <iomanip>
#include <string>

using namespace std;


void calculateOhmsLaw();
void checkPowerSafety(double voltage, double current);
void calculateEquivalentResistance();

int main()
{
	int choice;

	do
	{
		cout << "\n=============================================" << endl;
		cout << "   ENGINEERING CIRCUIT DIAGNOSTIC TOOL" << endl;
		cout << "=============================================" << endl;
		cout << "1. Ohm's Law & Power Analysis" << endl;
		cout << "2. Series/Parallel Circuit Analysis" << endl;
		cout << "3. Exit" << endl;
		cout << "Selection: ";
		cin >> choice;
		system("cls");

		if (choice == 1)
		{
			calculateOhmsLaw();
		}
		else if (choice == 2)
		{
			calculateEquivalentResistance();
		}
	} while (choice != 3);

	cout << endl;
	cout << "Diagnostic complete. Please press enter to exit..." << endl;

	cin.ignore(1000, '\n');
	cin.get();

	return 0;
}

void calculateOhmsLaw()
{
	int mode;
	double v, i, r;

	cout << endl;
	cout << "===Ohm's Law Mode===" << endl;
	cout << "1. Calculate Voltage (V = I * R)" << endl;
	cout << "2. Calculate Current (I = V / R)" << endl;
	cout << "3. Calculate Resistance (R = V / I)" << endl;
	cout << "Selection: ";
	cin >> mode;

	switch (mode)
	{
	case 1:
		cout << "Enter Current (A): ";
		cin >> i;
		cout << "Enter Resistance (Ohms): ";
		cin >> r;

		v = i * r;
		cout << fixed << setprecision(2) << "Calculated Voltage: " << v << " V" << endl;
		checkPowerSafety(v, i);
		break;

	case 2:
		cout << "Enter Voltage (V): ";
		cin >> v;
		cout << "Enter Resistance (Ohms): ";
		cin >> r;

		if (r == 0)
		{
			cout << "Error: Resistance cannot be zero (Risk of a shirt circuit)." << endl;
		}
		else
		{
			i = v / r;
			cout << fixed << setprecision(2) << "Calculated Current: " << i << " A" << endl;
			checkPowerSafety(v, i);
		}
		break;

	case 3:
		cout << "Enter Voltage (V): ";
		cin >> v;
		cout << "Enter Current (A): ";
		cin >> i;

		if (i == 0)
		{
			cout << "Error: Current cannot be zero (Open Circuit)." << endl;
		}
		else
		{
			r = v / i;

			cout << fixed << setprecision(2) << "Calculated Resistance: " << r << " Ohms" << endl;
			checkPowerSafety(v, i);
		}
		break;

	default:
		cout << "Invalid selection." << endl;
	}
}
void checkPowerSafety(double voltage, double current)
{
	double power = voltage * current;

	cout << "Power Dissipation: " << power << " W" << endl;

	if (power > 0.25)
	{
		cout << "[WARNING]: Power exceeds 0.25W safety threshold!" << endl;
	}
	else
	{
		cout << "[SAFE]: Power is within standard component limits." << endl;
	}
}

void calculateEquivalentResistance()
{
	int type, numResistors;
	double totalR = 0;
	double currentInput;

	cout << endl;
	cout << "===Network Analysis Mode===" << endl;
	cout << "1. Series Circuit (R1 + R2 +...)" << endl;
	cout << "2. Parallel Circuit (1/R1 + 1/R2 +...)" << endl;
	cout << "Selection: ";
	cin >> type;

	cout << "Number of resistors in the network: ";
	cin >> numResistors;

	for (int i = 0;i < numResistors;i++)
	{
		cout << "Enter value for Resistor " << i + 1 << " (Ohms): ";
		cin >> currentInput;

		if (type == 1)
		{
			totalR += currentInput;
		}
		else if(currentInput!=0)
		{
			totalR += (1.0 / currentInput);
		}
	}

	if (type == 2 && totalR != 0)
	{
		totalR = 1.0 / totalR;
	}

	cout << fixed << setprecision(2) << "Total Equivalent Rsistance: " << totalR << " Ohms" << endl;
}

