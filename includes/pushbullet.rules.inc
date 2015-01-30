<?php

/**
 * @file
 * Provide Rules integration.
 */

/**
 * Implements hook_rules_action_info().
 */
function pushbullet_rules_action_info() {
  return array(
    // Push Note.
    'pushbullet_rules_push_note' => array(
      'label' => t('Push note'),
      'group' => 'Pushbullet',
      'parameter' => array(
        'push_access_token' => array(
          'type' => 'text',
          'label' => t('Access token'),
          'description' => t('Pushbullet access token.'),
        ),
        'push_title' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Push title'),
        ),
        'push_body' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Push body'),
        ),
        'push_recipient' => array(
          'type' => 'text',
          'label' => t('Recipient'),
          'optional' => TRUE,
          'description' => t("Each push has a target, if you don't specify a target, pushbullet will broadcast it to all of the user's devices."),
        ),
      ),
    ),
    // Push Link.
    'pushbullet_rules_push_link' => array(
      'label' => t('Push link'),
      'group' => 'Pushbullet',
      'parameter' => array(
        'push_access_token' => array(
          'type' => 'text',
          'label' => t('Access token'),
          'description' => t('Pushbullet access token.'),
        ),
        'push_title' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Push title'),
        ),
        'push_body' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Push body'),
        ),
        'push_url' => array(
          'type' => 'text',
          'label' => t('Push URL'),
        ),
        'push_recipient' => array(
          'type' => 'text',
          'label' => t('Recipient'),
          'optional' => TRUE,
          'description' => t("Each push has a target, if you don't specify a target, pushbullet will broadcast it to all of the user's devices."),
        ),
      ),
    ),
    // Push Address.
    'pushbullet_rules_push_address' => array(
      'label' => t('Push address'),
      'group' => 'Pushbullet',
      'parameter' => array(
        'push_access_token' => array(
          'type' => 'text',
          'label' => t('Access token'),
          'description' => t('Pushbullet access token.'),
        ),
        'push_title' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Address name'),
        ),
        'push_address' => array(
          'type' => 'text',
          'label' => t('Address'),
        ),
        'push_recipient' => array(
          'type' => 'text',
          'label' => t('Recipient'),
          'optional' => TRUE,
          'description' => t("Each push has a target, if you don't specify a target, pushbullet will broadcast it to all of the user's devices."),
        ),
      ),
    ),
    // Push List.
    'pushbullet_rules_push_list' => array(
      'label' => t('Push list'),
      'group' => 'Pushbullet',
      'parameter' => array(
        'push_access_token' => array(
          'type' => 'text',
          'label' => t('Access token'),
          'description' => t('Pushbullet access token.'),
        ),
        'push_title' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Push title'),
        ),
        'push_items' => array(
          'type' => 'text',
          'label' => t('Push items'),
          'description' => t('Each list item must start from new line.')
        ),
        'push_recipient' => array(
          'type' => 'text',
          'label' => t('Recipient'),
          'optional' => TRUE,
          'description' => t("Each push has a target, if you don't specify a target, pushbullet will broadcast it to all of the user's devices."),
        ),
      ),
    ),
    // Push File.
    'pushbullet_rules_push_file' => array(
      'label' => t('Push file'),
      'group' => 'Pushbullet',
      'parameter' => array(
        'push_access_token' => array(
          'type' => 'text',
          'label' => t('Access token'),
          'description' => t('Pushbullet access token.'),
        ),
        'push_file_name' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('File name'),
        ),
        'push_file_type' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('File MIME type'),
        ),
        'push_file_url' => array(
          'type' => 'text',
          'label' => t('File URL'),
        ),
        'push_body' => array(
          'type' => 'text',
          'optional' => TRUE,
          'label' => t('Push body'),
        ),
        'push_recipient' => array(
          'type' => 'text',
          'label' => t('Recipient'),
          'optional' => TRUE,
          'description' => t("Each push has a target, if you don't specify a target, pushbullet will broadcast it to all of the user's devices."),
        ),
      ),
    ),
  );
}

/**
 * Push a note.
 *
 * @param $access_token
 * @param $title
 * @param $body
 */
function pushbullet_rules_push_note($access_token, $title = '', $body = '', $recipient = NULL) {
  $push = new Pushbullet($access_token);
  $push->pushNote($title, $body, $recipient);
}

/**
 * Push a link.
 *
 * @param $access_token
 * @param string $title
 * @param string $body
 * @param $url
 */
function pushbullet_rules_push_link($access_token, $title = '', $body = '', $url, $recipient = NULL) {
  $push = new Pushbullet($access_token);
  $push->pushLink($title, $body, $url, $recipient);
}

/**
 * Push an address.
 *
 * @param $access_token
 * @param string $name
 * @param $address
 */
function pushbullet_rules_push_address($access_token, $name = '', $address, $recipient = NULL) {
  $push = new Pushbullet($access_token);
  $push->pushAddress($name, $address, $recipient);
}

/**
 * Push a list.
 *
 * @param $access_token
 * @param string $title
 * @param $list
 */
function pushbullet_rules_push_list($access_token, $title = '', $list, $recipient = NULL) {
  $prepared_list = explode(PHP_EOL, $list);
  $push = new Pushbullet($access_token);
  $push->pushList($title, $prepared_list, $recipient);
}

/**
 * Push a file.
 *
 * @param $access_token
 * @param $file_type
 * @param string $file_name
 * @param $file_url
 * @param string $body
 */
function pushbullet_rules_push_file($access_token, $file_type, $file_name = '', $file_url, $body = '', $recipient = NULL) {
  if (!$file_type) {
    $curl = curl_init();
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
    curl_setopt($curl, CURLOPT_URL, $file_url);
    curl_setopt($curl, CURLOPT_CONNECTTIMEOUT, 20);
    curl_setopt($curl, CURLOPT_FOLLOWLOCATION, TRUE);
    curl_setopt($curl, CURLOPT_HEADER, TRUE);
    curl_setopt($curl, CURLOPT_NOBODY, TRUE);
    curl_exec($curl);
    $file_type = curl_getinfo($curl, CURLINFO_CONTENT_TYPE);
    curl_close($curl);
  }

  $push = new Pushbullet($access_token);
  $push->pushFile($file_name, $file_type, $file_url, $body, $recipient);
}
