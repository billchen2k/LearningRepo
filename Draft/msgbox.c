#include <CoreFoundation/CoreFoundation.h>
#include <string.h>

void MessageBox(char *header, char *message) {
	
	CFStringRef header_ref = CFStringCreateWithCString(NULL, header, strlen(header));
	CFStringRef message_ref = CFStringCreateWithCString(NULL, message, strlen(message));
	CFOptionFlags result;
	CFUserNotificationDisplayAlert(
	    0,
	    kCFUserNotificationNoteAlertLevel,
	    NULL,
	    NULL,
	    NULL,
	    header_ref,
	    message_ref,
	    NULL,
	    CFSTR("Cancel"),
	    NULL,
	    &result);

	CFRelease(header_ref);
	CFRelease(message_ref);
}

int main(){
	char header[] = "系统提示";
	char title[] = "wbs wmy";
	MessageBox(header, title);
}
