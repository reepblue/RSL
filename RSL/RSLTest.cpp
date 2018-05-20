// Demo RSL file

#include "RSL.h"

int main()
{
	// Test basic printing and logging
	RSL::Print("Hello world!");

	// Print with colors and log.
	RSL::Print("C", RSL::MESSAGE_RED);
	RSL::Print("O", RSL::MESSAGE_YELLOW);
	RSL::Print("L", RSL::MESSAGE_GREEN);
	RSL::Print("O", RSL::MESSAGE_CYAN);
	RSL::Print("R", RSL::MESSAGE_MAGENTA);

	// Do not log this
	RSL::Print("Look for me in the log file, honk-honk...", RSL::MESSAGE_DEFAULT, false);

	// Print and log the current time. 
	RSL::Print(RSL::GetCurrentDateTime());

	// Test basic input. The inquiry will log.
	std::string s = RSL::WaitForInput("What is your name?");

	// Have the app reply, but make it personal and don't log...
	RSL::Print("Hi, " + s + "! My name is Jeff.", RSL::MESSAGE_DEFAULT, false);

	// Another inquiry, but don't log...
	s = RSL::WaitForInput("How old are you?", false);

	// Test Debugging events
	RSL::Print("Creating debugging event..");
	RSL::Debug::Event e("Test");
	RSL::Debug::InitEvent(&e);

	for (int i=0; i <= 1000; i++ )
	{
		RSL::Print(i, RSL::MESSAGE_RED, false);
	}

	RSL::Debug::EndEvent(&e);

	// Test filesystem stuff.
	RSL::Print(RSL::FileSystem::GetDir());
	RSL::Print(RSL::FileSystem::GetAppDataPath());
	RSL::Print(RSL::FileSystem::GetDocumentsPath());

	bool b = RS_CreateDir("Sam");

	if (b)
	{
		RSL::Print("Yay!");
	}
	else
	{
		RSL::Print("Folder wasn't made. Maybe it already exists?");
	}

	// Test Config system.
	RSL::Config config("test.cfg");

	if (!RSL::FileSystem::Exists_s(config.GetFullPath()))
	{
		config.WriteKeyValue("test","1");
		config.SaveOut();	
	}

	RSL::Print(config.GetKeyValue("test"), RSL::MESSAGE_MAGENTA);
	
	// Write out the vector to the log file.
	RSL::WriteOut();

	// Hang until Enter/Return is pressed..
	RSL::PauseApp();
	return 0;
}
