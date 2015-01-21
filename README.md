# Pushbullet
Pushbullet boilerplate for feature Drupal integration, maybe.

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
~~~
