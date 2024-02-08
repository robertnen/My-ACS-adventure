package org.example;

import java.util.ArrayList;
import java.util.List;

public final class RequestsHolder {
    private static List<Request> adminRequests = null;

    public RequestsHolder() {}

    public List<Request> getAdminRequests() {
        if (adminRequests == null)
            adminRequests = new ArrayList<>();

        return adminRequests;
    }

    public boolean addRequest(Request request) {
        return this.getAdminRequests().add(request);
    }

    public boolean removeRequest(Request request) {
        if (this.getAdminRequests().contains(request))
            return this.getAdminRequests().remove(request);

        return false;
    }
}
