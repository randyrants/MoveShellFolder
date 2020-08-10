# MoveShellFolder
In my current job, I find that I'm re-installing Windows on several PC's every Monday and then using the PC's for the rest of the week.  Installing Windows is pretty simple but having used Windows for several decades there are some tweaks and configuration things that I do on each box that makes my life easier.  Some of these are already easily automated through CMD, Registry files, or PowerShell scripts.  Some are not.

One of the things that I started doing with Windows 98 or Windows 2000 - too long ago to remember for certain - is to "move" certain Shell folders from their default location to the root of the C: drive.  Why?  Because when I'm using a UNC path to get to the machine \\machinename\c$\Desktop is a heck of a lot shorter than \\machinename\c$\Users\UserName\Desktop.  Why not just use some folders off C:\ to store content?  I actually did that for a long while, but over time, I began to appreciate that Windows was creating folders like this for me and it became obvious that the "My Documents" concept was going to stick around for a while so, I figured it would be neat to bend the feature to do the best of both worlds.

In the old days, this was done with a simple Registry key change.  In recent days, Windows 10 gives you a ton of warning not to make this change with the Registry: you either have to do make the change using the property sheets for the folder or call the SHSetFolderLocation API.  The property page works very well: it not only creates the new directory, moves the files from old to new location, but it also updates the Shell to reflect the changes.  The SHSetFolderLocation API does not.  And I tried calling it from a Win32 app, from PowerShell, with and without Administrator privledges - it just doesn't happen.

After spelunking through some other examples, I discovered a COM interface that would do some of what I wanted the "move" to do.  Or at least enough of the functionality that I wanted it to, so I now have a single utility that will move some Shell folders and update the Shell as I want it to.

Why share the source?  Based off the examples I found online - or lack there of - not many people are using this API, so I'm adding the source here so I can keep a live back up and to share the knowledge I've collected by my searches and research.

What are next steps?  I suppose that the main() function can be updated to take in command line parameters so it can move the content all over.  Since it's a hybrid of managed C++ and COM, there could also be some bug fixes that prevent memory leaks, although I do not see people calling this CMD app very often.  As per all of my other projects, I'm happy to merge in pull requests after reviewing them, and updating the source as new things come around.

Thanks!
