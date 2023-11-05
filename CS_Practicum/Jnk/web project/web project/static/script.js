document.addEventListener('DOMContentLoaded', function() {
    const sidePanel = document.getElementById('sidePanel');
    const currentIdElement = document.getElementById('currentId');
    const idPhotoElement = document.getElementById('idPhoto');
    const currentStatusElement = document.getElementById('currentStatus');

    function showIdDetails(idData) {
        currentIdElement.textContent = idData[0];
        idPhotoElement.src = `/${idData[2]}`;
        currentStatusElement.textContent = idData[1];
    }

    function updateStatus(id, status) {
        currentStatusElement.textContent = status;

        fetch(`/update_status/${id}/${status}`)
            .then(response => response.text())
            .then(data => console.log(data))
            .catch(error => console.error('Error:', error));
    }

    sidePanel.addEventListener('click', function(event) {
        if (event.target && event.target.classList.contains('id-entry')) {
            const id = parseInt(event.target.dataset.id);
            const idData = ids.find(data => data[0] === id);
            showIdDetails(idData);
        }
    });

    document.getElementById('criminalButton').addEventListener('click', function() {
        const id = parseInt(currentIdElement.textContent);
        updateStatus(id, 'Criminal');
    });
    
    document.getElementById('notCriminalButton').addEventListener('click', function() {
        const id = parseInt(currentIdElement.textContent);
        updateStatus(id, 'Not Criminal');
    });
    
    document.getElementById('junkButton').addEventListener('click', function() {
        const id = parseInt(currentIdElement.textContent);
        updateStatus(id, 'Junk');
    });
});
