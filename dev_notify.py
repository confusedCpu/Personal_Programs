#!/usr/bin/python3

'''
name:       dev_notify
desc:       Detects new devices connected and sends a notification
requires:   pyudev (udev events), pgi (notifications)
'''


from pgi.repository import Notify
import pyudev
import subprocess

# Dictionary of messages that are sent with notifications
# TODO There must be a better way to do this.... I wish switch/case was a thing
gActions: dict = {
    'add':      '"{} - Added"',
    'remove':   '-u critical "{} - Removed"',
    'change':   '"{} - Changed"',
    'online':   '"{} - Online"',
    'offline':  '-u critical "{} - Offline"',
    'bind':     '"{} - Bound"',
    'unbind':   '-u critical "{} - Unbound"'
}


# send a notification to the screen, called by an event handler
# uses notify-send
def notify(message: str, action: str) -> None:
    full_message = gActions.get(action).format(message)
    print("** SENDING NOTIFICATION: {}".format(full_message))
    subprocess.Popen("notify-send {}".format(full_message), shell=True)


def notify2(name: str, var1: str, var2: str, action: str):

    summary = gActions.get(action)
    body = "\n{} {}".format(var1, var2)
    Notify.init('dev_notify')
    Notify.Notification.new(
        # summary
        summary.format(name),
        # message body
        "\n{} {}".format(var1, var2),
        # icon path
        "stuff",
    ).show()
    print("** NOTIFY2: {} - {}".format(summary, body))


# handle disk events
def disk_event(device: pyudev.Device) -> str:

    output: str = subprocess.Popen(
        "lsblk -nOP {}".format(device.device_node), shell=True, stdout=subprocess.PIPE
    ).stdout.readline()

    try:
        name: str = output[output.find(b"MODEL"):].split(b'"')[
            1].strip().decode('UTF-8')
    except:
        name: str = device.device_node

    try:
        size: str = output[output.find(b"SIZE"):].split(b'"')[
            1].strip().decode('UTF-8')
    except:
        size: str = ""

    notify(
        "{}: {}".format(name, size),
        device.action
    )

    notify2(name, "Size: {}".format(size), "", device.action)


# handle partition events
# TODO intergrate with automount here
# TODO write automount
def part_event(device: pyudev.Device) -> None:

    try:
        output: str = subprocess.Popen(
            "lsblk -nOP {}".format(device.device_node), shell=True, stdout=subprocess.PIPE
        ).stdout.readline()

        fstype: str = output[output.find(b'FSTYPE'):].split(b'"')[
            1].strip().decode('UTF-8')
        lable: str = output[output.find(b'LABLE'):].split(b'"')[
            1].strip().decode('UTF-8')
        size: str = output[output.find(b'SIZE'):].split(b'"')[
            1].strip().decode('UTF-8')

    except:
        fstype: str = ''
        lable: str = device.device_node
        size: str = ''

    notify(
        "{}: {} {}".format(lable, fstype, size),
        device.action
    )


# handle usb_device events
def udevice_event(device, messages: dict) -> str:
    print("** A usb_device has been {}".format(device.action))
    if device.action in 'add|online|bind':
        pass
        # notify(
        # messages[device.action].format(
        # device.device_node,
        # device.attributes.asstring('manufacturer'),
        # device.attributes.asstring('product')
        # )
        # )
        # else:
        # notify(
        # messages[device.action].format(
        # device.device_node
        # )
        # )

        # Listen for events, filtering them so they are handled by the correct tool


def monitor() -> None:
    # create the monitor
    context = pyudev.Context()
    monitor = pyudev.Monitor.from_netlink(context)

    print("\nStarted monitoring!\n")

    # Listen for device messages in an infinite loop
    for device in iter(monitor.poll, None):
        # disk
        if device.subsystem == 'block' and device.device_type == 'disk':
            print("** Disk event detected - {}".format(device.action))
            disk_event(device)

        # partition
        elif device.subsystem == 'block' and device.device_type == 'partition':
            # part_event(device, gActions['partition'])
            print("** Partition event detected - {}".format(device.action))
            part_event(device)

            # input
        elif device.subsystem in 'usb' and device.device_type == 'usb_device':
            # udevice_event(device, gActions['usb_device'])
            continue


if __name__ == '__main__':
    monitor()
