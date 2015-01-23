# Pushbullet
Pushbullet API for Drupal.

This module provide Pushbullet API via code, and integrated with Rules module.

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
~~~
