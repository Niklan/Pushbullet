# Pushbullet
Pushbullet API for Drupal.

This module provide Pushbullet API via code, and integrated with Rules module.

![Push Rules example in Drupal 7](http://i.imgur.com/8oWReuQ.gif)

# Code examples
~~~php
// Initialize.
$pushbullet = new Pushbullet('YOUR ACCESS TOKEN');

// Send Note.
$pushbullet->pushNote('Title', 'Body.');

// Send Link.
$pushbullet->pushLink('Title', 'Body.', 'http://google.com/');

// Send Address.
$pushbullet->pushAddress('State of Liberty', 'Liberty Island, New York, NY, USA');

// Send List.
$pushbullet->pushList('Title', array(
  'Buy milk',
  'Buy coffee',
));

// Send File.
$pushbullet->pushFile('My cat', 'image/jpeg', 'http://example.com/cat.jpg', 'Body.');

// Get all Pushes.
$pushbullet->getPushes();

// Get pushes after 1 january 2015 00:00:00. (unix time)
$pushbullet->getPushes(1421866821);

// Dismiss push.
$pushbullet->dismissPush('IDEN');

// Change Push items for List push type.
$pushbullet->editPushItems('IDEN', array(
  'items' => array(
    array(
      'checked' => false,
      'text' => 'Test 1',
    ),
    array(
      'checked' => true,
      'text' => 'Test 2',
    ),
  ),
));

// Delete a push.
$pushbullet->deletePush('IDEN');

// Get list of devices.
$pushbullet->getDevices();

// Create new device.
$pushbullet->createDevice('name');

// Delete device.
$pushbullet->deleteDevice('IDEN');

// Get contact list.
$pushbullet->getContacts();

// Create contact.
$pushbullet->createContact('Name', 'email@address.com');

// Update contact name.
$pushbullet->updateContact('IDEN', 'New name');

// Delete contact.
$pushbullet->deleteContact('IDEN');

// Get user subscriptions.
$pushbullet->getSubscriptions();

// Subscribe to channel.
$pushbullet->subscribeToChannel('CHANNEL_TAG');

// Usubscribe from channel.
$pushbullet->unsubscribeFromChannel('IDEN');

// Get channel information.
$pushbullet->getChannelInfo('CHANNEL_TAG');

// Get user info.
$pushbullet->getUserInfo();

// Update user preferences.
// WARNING! Use it with caution. This function will override previous preferences.
// Don't forget to save them before.
$pushbullet->updateUserPreferences(array(
  'smile' => '(^_^)',
));

// Upload file to pushbullet server.
$pushbullet->uploadFile('README.md');

// Each push type can have recipient in last parameter.
// Parameter can be:
// device_iden - Send the push to a specific device. Appears as 
//               target_device_iden on the push. You can find this using the 
//               getDevices() call.
// email - Send the push to this email address. If that email address is 
//         associated with a Pushbullet user, we will send it directly to that
//         user, otherwise we will fallback to sending an email to the email 
//         address (this will also happen if a user exists but has no devices 
//         registered).
// channel_tag - Send the push to all subscribers to your channel that has 
//               this tag.
// In this case IDEN used on init will be use as sender.
$pushbullet->pushNote('Title', 'Body.', 'example@example.com');
~~~
